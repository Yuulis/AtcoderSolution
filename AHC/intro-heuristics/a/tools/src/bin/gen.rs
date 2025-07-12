#![allow(non_snake_case)]

use clap::Parser;
use rand::prelude::*;
use rand::{Rng, SeedableRng};
use std::{io::prelude::*, path::PathBuf};

#[derive(Parser, Debug)]
struct Cli {
    /// Path to seeds.txt
    seeds: String,
    /// Path to input directory
    #[clap(short = 'd', long = "dir", default_value = "in")]
    dir: PathBuf,
    #[clap(short, long)]
    /// Print input details in csv format
    verbose: bool,
}

fn generate_input(seed: u64) -> String {
    let mut rng = StdRng::seed_from_u64(seed);
    let D = 365;
    let c: Vec<i32> = (0..26).map(|_| rng.gen_range(0..=100)).collect();
    let s: Vec<Vec<i32>> = (0..D)
        .map(|_| (0..26).map(|_| rng.gen_range(0..=20000)).collect())
        .collect();

    let mut output = String::new();
    output.push_str(&format!("{}\n", D));
    output.push_str(
        &c.iter()
            .map(|x| x.to_string())
            .collect::<Vec<_>>()
            .join(" "),
    );
    output.push('\n');
    for sd in s {
        output.push_str(
            &sd.iter()
                .map(|x| x.to_string())
                .collect::<Vec<_>>()
                .join(" "),
        );
        output.push('\n');
    }
    output
}

fn main() {
    let cli = Cli::parse();
    if !std::path::Path::new(&cli.dir).exists() {
        std::fs::create_dir(&cli.dir).unwrap();
    }
    let f = std::fs::File::open(&cli.seeds).unwrap_or_else(|_| {
        eprintln!("no such file: {}", cli.seeds);
        std::process::exit(1)
    });
    let f = std::io::BufReader::new(f);
    let mut id = 0;
    if cli.verbose {
        println!("file,seed");
    }
    for line in f.lines() {
        let line = line.unwrap();
        let line = line.trim();
        if line.len() == 0 {
            continue;
        }
        let seed = line.parse::<u64>().unwrap_or_else(|_| {
            eprintln!("parse failed: {}", line);
            std::process::exit(1)
        });
        let input = generate_input(seed);
        if cli.verbose {
            println!("{:04},{}", id, seed);
        }
        let file_path = cli.dir.join(format!("{:04}.txt", id));
        let mut w =
            std::io::BufWriter::new(std::fs::File::create(&file_path).unwrap_or_else(|e| {
                eprintln!("Failed to create file {}: {}", file_path.display(), e);
                std::process::exit(1);
            }));
        write!(w, "{}", input).unwrap_or_else(|e| {
            eprintln!("Failed to write to file {}: {}", file_path.display(), e);
            std::process::exit(1);
        });
        id += 1;
    }
}
