# はじめに

このツールは、現代の AHC でよく付属しているローカルテスタの形式で[AtCoder Contest Scheduling](https://atcoder.jp/contests/intro-heuristics/tasks/intro_heuristics_a)用に thunder が作成した非公式ツールです。
公式で用意されているツールは他の AHC と形式が異なるため、[pahcer](https://github.com/terry-u16/pahcer)等の外部ツールを利用しづらいです。
そこで、pahcer 等の外部ツールを使いたい方や、現代の AHC の形式に慣れたい人のためにこのツールを作成しました。

# 使い方

## 実行環境

Rust 言語のコンパイル環境が必要です。
https://www.rust-lang.org/ja を参考に各自インストールして下さい。
コンパイルエラーになった場合、コンパイラのバージョンが古い可能性があります。
以下のコマンド実行することで最新のコンパイラに更新が可能です。

```
rustup update
```

以下の実行例では、この README が置かれているディレクトリに移動して作業することを想定しています。

## 入力生成

`in` ディレクトリに予め生成された seed=0~99 に対する入力ファイルが置かれています。
より多くの入力が欲しい場合は、`seeds.txt` に欲しい入力ファイルの数だけ乱数 seed 値(符号なし 64bit 整数値)を記入し、以下のコマンドを実行します。

```
cargo run -r --bin gen seeds.txt
```

生成された入力ファイルは `in` ディレクトリに出力されます。

## ビジュアライザ

入力ファイル名を`in.txt`、出力ファイル名を`out.txt`としたとき、以下のコマンドを実行します。

```
cargo run -r --bin vis in.txt out.txt
```

出力のビジュアライズ結果は `vis.html` というファイルに書き出されます。
標準出力にはスコアを出力します。

より機能が豊富な[ウェブ版の非公式ビジュアライザ](https://thun-c.github.io/visualizer/introduction/Visualizer.html)も利用可能です。
