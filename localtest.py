import os,subprocess,time
from concurrent import futures
from math import log10
from datetime import datetime

# 想定フォルダ構成
# <このフォルダ>
#   ├── test.py                     # このファイル
#   ├── <提出コード>
#   └── tools or tools_x86_64-pc-windows-gnu
#          ├── in/                  # テスト入力
#          ├── out/                 # テスト出力
#          ├── vis.exe              # ローカルテスタ実行ファイル ※windows用のコンパイル済みバイナリの場合
#          └── target/release/vis   # ローカルテスタ実行ファイル 

###### テスト実行設定

# プログラム実行コマンド
PROGRAM_CMD = os.path.expanduser("~/AtcoderSolution/a.out")

# テスト対象seed番号
START_SEED=0
SIZE=100
STEP=1


# 最大並列処理数
MAX_WORKERS = 16


# スコア表示文字列 # ローカルテスタ（ビジュアライザ）が出力する形式に合わせて変更する
TESTER_OUTPUT_SCORE_TXT = "Score ="


# ローカルテスタ テストコマンド (例：AHC027)
TESTER_DIR = "tools" # Windows用のコンパイル済みバイナリの場合は "tools_x86_64-pc-windows-gnu"
TESTER_CMD = "cargo run --release --bin vis"

# 入出力テストファイルフォルダ
TEST_IN_DIR = "in"
TEST_OUT_DIR = "out"


###### テスト実行設定 ここまで

problem_dir = os.getcwd()
TEST_IDS = list(range(START_SEED,START_SEED+SIZE*STEP,STEP)) # テスト対象seed番号リスト生成

class TaskInfo:
    def __init__(self, score:int, time:float, seed:int=0):
        self.score = score
        self.time = time
        self.seed = seed

class Task:
    @classmethod
    def execute(cls, input_file:str="", output_file:str="", seed:int=0):
        t_start = time.perf_counter()
        cmd = f"{PROGRAM_CMD}"
        if input_file:
            cmd += f" < \"{input_file}\""
        if output_file:
            cmd += f" 1> \"{output_file}\""
        result = subprocess.run(cmd,
                                stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE,
                                shell=True)
        t_end = time.perf_counter()
        # 実行エラーを検知したい場合は、 result.stderr.decode("utf-8","ignore") の結果を見る
        t_lapse = t_end - t_start
        ret = TaskInfo(score=0, time=t_lapse, seed=seed)
        # スコア計算
        execute_tester_command = f"{TESTER_CMD} {input_file} {output_file}"
        result = subprocess.run(execute_tester_command,
                                stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE,
                                cwd=os.path.join(problem_dir,TESTER_DIR),
                                shell=True)
        std_out = result.stdout.decode("utf-8", "ignore")
        for out in std_out.split("\n"):
            if TESTER_OUTPUT_SCORE_TXT in out:
                ret.score = int(out.split(TESTER_OUTPUT_SCORE_TXT)[1])
                break
        return ret

def task(seed:int, in_path:str, out_path:str) -> TaskInfo:
    if not os.path.exists(os.path.dirname(out_path)):os.makedirs(os.path.dirname(out_path))
    ret = Task.execute(input_file=in_path, output_file=out_path, seed=seed)
    return ret


if __name__ == '__main__':
    executor = futures.ThreadPoolExecutor(max_workers=MAX_WORKERS)

    t_test_start = time.perf_counter()
    tasks = []
    for seed in TEST_IDS:
        in_path = os.path.join(problem_dir, TESTER_DIR, TEST_IN_DIR, f"{seed:04}.txt")
        out_path = os.path.join(problem_dir, TESTER_DIR, TEST_OUT_DIR, f"{seed:04}.txt")
        if os.path.exists(in_path):
            tasks.append((executor.submit(task, seed, in_path, out_path), seed))

    task_results:list[TaskInfo] = []
    t_sum = 0
    for tsk, i_test in tasks:
        info:TaskInfo = tsk.result()
        task_results.append(info)
        t_ms = round(info.time * 1000)
        t_sum += t_ms
        print(f"{i_test:3d}  score:{info.score:12,d} "+f"{t_ms:5d} ms")

    scores = [r.score for r in task_results]
    total_score = sum(scores)
    
    positive_scores = [s for s in scores if s > 0]
    if positive_scores:
        average_log_score = sum([log10(s) for s in positive_scores]) / len(positive_scores)
    else:
        average_log_score = 0.0

    print()
    print(f"total   time: {(time.perf_counter() - t_test_start):.1f} s")
    print(f"average time: {t_sum/len(tasks):.0f} ms")
    print(f"sum score   : {total_score:,} pt")
    print(f"average(log): {average_log_score:.5}")

    # 結果保存
    RESULT_FILE = f"result_{datetime.now().strftime('%Y%m%d%H%M%S')}.csv"
    result_file_path = os.path.join(problem_dir, RESULT_FILE)
    fp = open(result_file_path, "w")

    fp.write(f"total  ,{sum(scores):10d}")
    fp.write("\n")
    fp.write(f"average log,{average_log_score:8.5f}\n")
    for r in task_results:
        fp.write(f"test{r.seed:03d},{r.score:d}\n")
