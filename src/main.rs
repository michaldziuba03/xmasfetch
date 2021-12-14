const RED: &str = "\x1b[31m";
const GREEN: &str = "\x1b[32m";
const WHITE: &str = "\x1b[0m";
const BOLD: &str = "\x1b[1m";


fn main() {
    let ascii_art = format!(
        "{red}      ,--.     {white}
{white}    ()   {red} \\    {white}
{red}     /     \\   {white}
{red}   _/_______\\  {white}
{white}  (__________) {white}
{white}   /  {green}@  @{white}  \\  {white}
{white}  (`._,{red}(){white}._,') {white}
{white}  (  `-'`-'  ) {white}
{white}   \\        /  {white}
{white}    \\,,,,,/    {white}
",
    red = RED,
    white = WHITE,
    green = GREEN,
);

    let mut final_result: Vec<String> = vec![];
    let art_lines = ascii_art.lines();

    for line in art_lines {
        let str_value = format_info("os".to_string(), "Linux Mint".to_string());
        println!("{}", str_value);
    }
}

fn format_info(title: String, value: String) -> String {
    return format!("{}{}{}: {}{}", BOLD, GREEN, title, WHITE, value);
}