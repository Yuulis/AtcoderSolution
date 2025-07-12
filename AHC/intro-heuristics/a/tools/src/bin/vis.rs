#![allow(non_snake_case)]

use tools::*;

fn main() {
    if std::env::args().len() != 3 {
        eprintln!(
            "Usage: {} <input> <output>",
            std::env::args().nth(0).unwrap()
        );
        return;
    }
    let in_file = std::env::args().nth(1).unwrap();
    let out_file = std::env::args().nth(2).unwrap();
    let input = std::fs::read_to_string(&in_file).unwrap_or_else(|_| {
        eprintln!("no such file: {}", in_file);
        std::process::exit(1)
    });
    let output = std::fs::read_to_string(&out_file).unwrap_or_else(|_| {
        eprintln!("no such file: {}", out_file);
        std::process::exit(1)
    });
    let input = parse_input(&input);
    let out = parse_output(&input, &output);

    let VisResult { score, err, svg } = match out {
        Ok(output_data) => vis(&input, &output_data),
        Err(e) => VisResult {
            score: 0,
            err: e.to_string(),
            svg: String::new(),
        },
    };

    if err.len() > 0 {
        eprintln!("{}", err);
        println!("Score = {}", 0);
    } else {
        println!("Score = {}", score);
    }
    let vis_html = format!("<html><body>\n{}\n</body></html>", svg);
    std::fs::write("vis.html", &vis_html).unwrap();
}
