# my-library

AtCoder 青色までに必要なアルゴリズム・データ構造のスニペット集。
各ファイルは **単体で完結** し、`g++ -std=c++17`（ACL 利用分は `-I ac-library`）でコンパイル可能。
ファイル冒頭に概要・計算量・用途・注意点をコメントで記載し、末尾の `main()` に使用例を付けています。

> **ACL（AtCoder Library）に含まれるものは原則として再実装しません。**
> DSU / Fenwick Tree / Segment Tree / Lazy Segtree / SCC / MaxFlow / MinCostFlow / TwoSAT /
> modint / Convolution(FFT) / Suffix Array / Z-algorithm / LCP / CRT / floor_sum / pow_mod / inv_mod
> は ACL を直接使ってください。

## technique/ — 基本テクニック
| ファイル | 内容 |
|---|---|
| `binary_search.cpp` | めぐる式二分探索（ok/ng）, `lower_bound`/`upper_bound`, 実数二分探索 |
| `prefix_sum.cpp` | 1次元累積和（区間和 `[l, r)`） |
| `imos_method.cpp` | いもす法（差分配列による区間加算） |
| `coordinate_compression.cpp` | 座標圧縮（sort + unique + lower_bound） |
| `two_pointers.cpp` | しゃくとり法 / スライディングウィンドウ |

## graph/ — グラフ
| ファイル | 内容 |
|---|---|
| `bfs.cpp` | 幅優先探索（重みなし最短路） |
| `dfs.cpp` | 深さ優先探索（再帰 / スタック両方） |
| `dijkstra.cpp` | ダイクストラ法（非負重み最短路） |
| `bellman_ford.cpp` | ベルマンフォード法（負辺・負閉路検出） |
| `floyd_warshall.cpp` | ワーシャルフロイド法（全点対最短路） |
| `topological_sort.cpp` | トポロジカルソート（Kahn 法） |
| `kruskal_mst.cpp` | 最小全域木（Kruskal, ACL dsu 使用） |
| `prim_mst.cpp` | 最小全域木（Prim） |
| `lca_doubling.cpp` | 最近共通祖先（ダブリング）+ 2 頂点間距離 |
| `tree_diameter.cpp` | 木の直径（2 回 BFS） |
| `bipartite_check.cpp` | 二部グラフ判定（2 彩色） |
| `cycle_detection.cpp` | 閉路検出（有向 / 無向） |
| `grid_bfs.cpp` | グリッド上の BFS（4 方向移動） |

## data_structure/ — データ構造
| ファイル | 内容 |
|---|---|
| `weighted_union_find.cpp` | 重み付き Union-Find（ポテンシャル） |
| `sparse_table.cpp` | Sparse Table（静的 RMQ, O(1) クエリ） |
| `trie.cpp` | トライ木（insert / countWord / countPrefix） |
| `cumulative_sum_2d.cpp` | 2 次元累積和（矩形和 O(1)） |

## mathmatics/ — 数学
| ファイル | 内容 |
|---|---|
| `gcd_lcm.cpp` | 最大公約数 / 最小公倍数（オーバーフロー対策） |
| `extended_euclid.cpp` | 拡張ユークリッドの互除法 + mod 逆元 |
| `eratosthenes_sieve.cpp` | エラトステネスの篩 |
| `linear_sieve.cpp` | 線形篩（最小素因数 SPF → 高速素因数分解） |
| `prime_number_check.cpp` | 素数判定 |
| `prime_factorization.cpp` | 素因数分解 |
| `divisor_enumeration.cpp` | 約数列挙 |
| `iterative_square_power_calculation.cpp` | 繰り返し二乗法（mod べき乗） |
| `modinv.cpp` | mod 逆元（フェルマーの小定理） |
| `combination_mod.cpp` | 二項係数 nCk（mod, ACL modint 使用） |
| `matrix_power.cpp` | 行列累乗（フィボナッチ例） |
| `radix_conversion.cpp` | 進数変換 |

## dp/ — 動的計画法
| ファイル | 内容 |
|---|---|
| `lis.cpp` | 最長増加部分列（O(N log N)） |
| `knapsack_01.cpp` | 0/1 ナップサック |

## strings/ — 文字列
| ファイル | 内容 |
|---|---|
| `rolling_hash.cpp` | ローリングハッシュ（部分文字列比較 O(1)） |
| `kmp.cpp` | KMP 法（接頭辞関数・パターンマッチ） |
| `run_length_encoding.cpp` | ランレングス圧縮 |
| `palindrome_check.cpp` | 回文判定 |
| `string_split.cpp` | 文字列分割 |
| `conversion_between_numeric_and_string.cpp` | 数値 ⇔ 文字列変換 |
