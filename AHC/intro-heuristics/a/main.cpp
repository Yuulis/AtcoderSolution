#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr auto INFL = 1LL << 60;

// ======================================== //

struct Input
{
    /// @brief 日数(D = 365 で固定)
    int length;
    /// @brief 各コンテストの満足度の下がりやすさ
    vector<int> satisfaction_decrease;
    /// @brief ある日の各コンテストの満足度の増加値
    vector<vector<int>> satisfaction_increase;

    /// @brief 入力データの読み込み
    /// @return 入力データ
    static Input read()
    {
        int D;
        cin >> D;
        vector<int> c(26);
        for (int i = 0; i < 26; ++i)
        {
            cin >> c[i];
        }
        vector<vector<int>> s(D, vector<int>(26));
        for (int i = 0; i < D; ++i)
        {
            for (int j = 0; j < 26; ++j)
            {
                cin >> s[i][j];
            }
        }

        return Input{D, c, s};
    }
};

struct Output
{
    /// @brief ある日に開催されるコンテストのタイプ
    vector<int> contest_types;

    /// @brief 解を出力する
    void print()
    {
        for (int i = 0; i < (int)contest_types.size(); i++)
        {
            cout << contest_types[i] + 1 << endl;
        }

        return;
    }
};

/// @brief 満足度(score)計算用の関数
/// @param input 入力データ
/// @param contest_types 各日のコンテストのタイプを表す配列(長さ d_l)
/// @return d_l 日目時点での満足度
ll evaluate(const Input &input, const vector<int> &contest_types)
{
    ll score = 0;
    vector<int> last(26, 0);

    for (int d = 0; d < (int)contest_types.size(); d++)
    {
        last[contest_types[d]] = d + 1;

        for (int i = 0; i < 26; i++)
        {
            score -= (ll)input.satisfaction_decrease[i] * ((d + 1) - last[i]);
        }

        score += input.satisfaction_increase[d][contest_types[d]];
    }

    return score;
}

/// @brief 貪欲解を求める
/// @param input : 入力データ
/// @note 貪欲法では, 各日ごとに最良なコンテストのタイプを選ぶことで, 満足度を最大化するようにコンテストを開催する
/// @return 出力データ
Output greedy_solve(const Input &input)
{
    /// @brief contest_types[d] := d 日目に開催されるコンテストのタイプ
    vector<int> contest_types;

    for (int d = 0; d < input.length; d++)
    {
        /// @brief d 日目に開催するコンテストとして最良なもの
        int best_type = -1;
        /// @brief 現時点での最良な満足度
        ll best_score = -INFL;

        for (int i = 0; i < 26; i++)
        {
            contest_types.push_back(i);

            ll current_score = evaluate(input, contest_types);
            if (current_score > best_score)
            {
                best_score = current_score;
                best_type = i;
            }

            contest_types.pop_back();
        }

        // d 日目に開催するコンテストのタイプを最良のものに確定
        contest_types.push_back(best_type);
    }

    return Output{contest_types};
}

Output solve(const Input &input)
{
    /// @brief contest_types[d] := d 日目に開催されるコンテストのタイプ
    /// @note 貪欲法で求めた解を初期解とする
    vector<int> contest_types = greedy_solve(input).contest_types;
    /// @brief 現時点での満足度
    ll current_score = evaluate(input, contest_types);

    /// @brief 乱数生成器
    mt19937 rand{42};
    /// @brief 0.0 以上 1.0 未満の乱数を生成する
    uniform_real_distribution<double> rand_01(0.0, 1.0);

    /// @brief 焼きなまし法の開始時刻
    auto start_time = chrono::system_clock::now();
    /// @brief 制限時間(ミリ秒単位)
    const int LIMIT = 1900;

    /// @brief 焼きなましの開始温度
    const double START_TEMP = 2e3;
    /// @brief 焼きなましの終了温度
    const double END_TEMP = 6e2;
    /// @brief 現在の温度
    double current_temperature = START_TEMP;

    /// @brief 試行回数
    int iteration = 0;

    while (true)
    {
        auto current_time = chrono::system_clock::now();

        // 制限時間を超えたら終了
        if (chrono::duration_cast<chrono::milliseconds>(current_time - start_time).count() >= LIMIT)
        {
            break;
        }

        // 確率 1/2 で, 一点更新か二点 Swap かのいずれかを選ぶ
        // 一点更新 : ある日のコンテストのタイプを変更
        if (rand() % 2 == 0)
        {
            // 変更する日数とコンテストのタイプをランダムに選ぶ
            int d = rand() % input.length;
            int type = rand() % 26;

            // 元のコンテストのタイプを保存
            int old_type = contest_types[d];

            // d 日目のコンテストのタイプを変更
            contest_types[d] = type;

            // 満足度を計算
            ll new_score = evaluate(input, contest_types);

            if (current_score < new_score || rand_01(rand) < exp((new_score - current_score) / current_temperature))
            {
                cerr << "iteration: " << iteration << ", new score = " << new_score << endl;
                current_score = new_score;
            }
            // 満足度が改善されなかった場合, 元に戻す
            else
            {
                contest_types[d] = old_type;
            }
        }
        // 二点 Swap: 比較的近い2つの日のコンテストのタイプを入れ替える
        else
        {
            // 入れ替える日をランダムに選ぶ
            int d1 = rand() % input.length;
            int d2 = d1 + (rand() % (min(input.length - 1, d1 + 14) - d1 + 1));

            // 実際に Swap
            swap(contest_types[d1], contest_types[d2]);

            ll new_score = evaluate(input, contest_types);
            if (current_score < new_score || rand_01(rand) < exp((new_score - current_score) / current_temperature))
            {
                cerr << "iteration: " << iteration << ", new score = " << new_score << endl;
                current_score = new_score;
            }
            // 満足度が改善されなかった場合, 元に戻す
            else
            {
                swap(contest_types[d1], contest_types[d2]);
            }
        }

        iteration++;

        double progress = (double)chrono::duration_cast<chrono::milliseconds>(current_time - start_time).count() / (double)LIMIT;
        current_temperature = pow(START_TEMP, 1.0 - progress) * pow(END_TEMP, progress);
    }

    cerr << "total iterations: " << iteration << endl;

    return Output{contest_types};
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Input input = Input::read();

    Output output = solve(input);

    output.print();

    return 0;
}