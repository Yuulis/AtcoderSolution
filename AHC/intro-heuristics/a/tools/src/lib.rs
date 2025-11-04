#![allow(non_snake_case, unused_macros, unused_imports, dead_code)]

use anyhow::{anyhow, bail, ensure, Result};
use itertools::Itertools;
use proconio::input;
use std::cmp::max;
use std::ops::RangeBounds;
use svg::node::element::{Rectangle, Style, Text, Title};
use svg::Document;

#[derive(Clone, Debug)]
pub struct Input {
    D: usize,
    c: Vec<i64>,
    s: Vec<Vec<i64>>,
}

pub fn parse_input(f: &str) -> Input {
    let f = proconio::source::once::OnceSource::from(f);
    input! {
        from f,
        D: usize,
        c: [i64; 26],
        s: [[i64; 26]; D],
    }
    Input { D, c, s }
}

pub fn read<T: Copy + PartialOrd + std::fmt::Display + std::str::FromStr, R: RangeBounds<T>>(
    token: Option<&str>,
    range: R,
) -> Result<T> {
    if let Some(v) = token {
        if let Ok(v) = v.parse::<T>() {
            ensure!(range.contains(&v), "Out of range: {}", v);
            Ok(v)
        } else {
            bail!("Parse error: {}", v)
        }
    } else {
        bail!("Unexpected EOF")
    }
}

#[derive(Debug, Clone)]
pub struct Output {
    pub t: Vec<i32>,
}

pub fn parse_output(input: &Input, f: &str) -> Result<Output> {
    let mut out = vec![];
    let mut tokens = f.split_whitespace();

    for _d in 0..input.D {
        let val = read(tokens.next(), 1..=26)?;
        out.push(val);
    }

    if tokens.next().is_some() {
        bail!("Too many output values");
    }

    Ok(Output { t: out })
}

fn color(val: f64) -> (u8, u8, u8) {
    let val = val.max(0.0).min(1.0);
    let tmp = ((-(2.0 * std::f64::consts::PI * val).cos()) / 2.0 + 0.5) * 255.0;
    let tmp = tmp.round().max(0.0).min(255.0) as u8;
    if val >= 0.5 {
        (255, tmp, 0)
    } else {
        (tmp, 255, 0)
    }
}

pub fn rect(x: f64, y: f64, w: f64, h: f64, fill: String) -> Rectangle {
    Rectangle::new()
        .set("x", x)
        .set("y", y)
        .set("width", w)
        .set("height", h)
        .set("fill", fill)
        .set("stroke", "grey")
        .set("stroke-width", 1)
}

pub fn text(x: f64, y: f64, size: f64, content: &str) -> Text {
    Text::new(content)
        .set("x", x)
        .set("y", y)
        .set("font-size", size)
        .set("text-anchor", "start")
}

pub fn vis(input: &Input, out: &Output) -> VisResult {
    let mut sat: i64 = 0;
    let mut last = vec![0i64; 26];
    let mut err = String::new();

    for d in 0..input.D {
        if !(1 <= out.t[d] && out.t[d] <= 26) {
            err = format!(
                "Day {}: Contest index {} is out of range [1, 26].",
                d + 1,
                out.t[d]
            );
            return VisResult {
                score: 0,
                err,
                svg: String::new(),
            };
        }
        let current_contest_idx = (out.t[d] - 1) as usize;

        sat += input.s[d][current_contest_idx];
        last[current_contest_idx] = (d + 1) as i64;

        for i in 0..26 {
            sat -= input.c[i] * ((d + 1) as i64 - last[i]);
        }
    }
    let score = max(0, 1_000_000 + sat);

    let rect_w = 40.0;
    let rect_h = 10.0;
    let padding = 1.0;
    let font_size = 7.0;
    let text_offset_x = 10.0;
    let text_offset_y = 9.0;

    let width = 26.0 * rect_w + 2.0 * padding;
    let height = rect_h + (input.D as f64) * rect_h + 20.0 * padding;

    let mut doc = Document::new()
        .set("viewBox", (0, 0, width, height))
        .set("width", width)
        .set("height", height);

    for i in 0..26 {
        let (r, g, b) = color(input.c[i] as f64 / 100.0);
        let fill_color = format!("#{:02x}{:02x}{:02x}", r, g, b);
        let x = (i as f64) * rect_w + padding;
        let y = padding;
        doc = doc.add(rect(x, y, rect_w, rect_h, fill_color));
        doc = doc.add(text(
            x + text_offset_x,
            y + text_offset_y,
            font_size,
            &input.c[i].to_string(),
        ));
    }

    let s_start_y = rect_h + padding * 2.0;
    for d in 0..input.D {
        for i in 0..26 {
            let (r, g, b) = color(input.s[d][i] as f64 / 20000.0);
            let fill_color = format!("#{:02x}{:02x}{:02x}", r, g, b);
            let x = (i as f64) * rect_w + padding;
            let y = s_start_y + (d as f64) * rect_h + padding;
            doc = doc.add(rect(x, y, rect_w, rect_h, fill_color));
            doc = doc.add(text(
                x + text_offset_x,
                y + text_offset_y,
                font_size,
                &input.s[d][i].to_string(),
            ));
        }
    }

    for d in 0..input.D {
        let contest_idx = (out.t[d] - 1) as usize;
        let x = (contest_idx as f64) * rect_w + padding;
        let y = s_start_y + (d as f64) * rect_h + padding;
        let highlight_rect = Rectangle::new()
            .set("x", x)
            .set("y", y)
            .set("width", rect_w)
            .set("height", rect_h)
            .set("fill", "none")
            .set("stroke", "black")
            .set("stroke-width", 3);
        doc = doc.add(highlight_rect);
    }

    VisResult {
        score,
        err,
        svg: doc.to_string(),
    }
}

pub struct VisResult {
    pub score: i64,
    pub err: String,
    pub svg: String,
}
