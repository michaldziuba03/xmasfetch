mod info;

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

    let art_lines = ascii_art.lines();
    let info_vector = get_info();

    for (i, art_line) in art_lines.enumerate() {
        let info_element = info_vector.get(i);
        
        if info_element.is_none() {
            println!("{}", art_line);
        } else {
            println!("{}  {}", art_line, info_element.unwrap());
        }
    }
}

fn get_info() -> Vec<String> {
    let user = info::get_user();
    let host = info::get_host();
    let os = info::get_os();
    let kernel = info::get_kernel();
    let shell = info::get_shell();
    let uptime = info::get_uptime();
    let memory = info::get_memory();

    return [
        "".to_string(),
        format_host(user, host),
        draw_dash(),
        format_info(" os", os),
        format_info(" kernel", kernel),
        format_info(" shell", shell),
        format_info(" uptime", uptime),
        format_info(" memory", memory),
    ].to_vec();
}

fn format_host(user: String, host: String) -> String {
    return format!("{bold}{red}{user}{white}@{bold}{red}{host}", 
        red = RED, 
        user = user, 
        white = WHITE, 
        host = host,
        bold = BOLD,
    );
}

fn draw_dash() -> String {
    let dash = "────────────────────────────";

    return format!("{}{}{}", BOLD, WHITE, dash);
}

fn format_info(title: &str, value: String) -> String {
    return format!("{}{}{}: {}{}", BOLD, GREEN, title, WHITE, value);
}