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
    let info_array = get_info().unwrap();

    for (i, art_line) in art_lines.enumerate() {
        let info_element = info_array.get(i);
        
        if info_element.is_none() {
            println!("{}", art_line);
        } else {
            println!("{}  {}", art_line, info_element.unwrap());
        }
    }
}

fn get_info() -> Option<[String; 8]> {
    let info = xmasfetch::OSInfo::new();
    let user = info.user()?;
    let host = info.hostname()?;
    let os = info.os()?;
    let kernel = info.kernel()?;
    let shell = info.shell()?;
    let uptime = info.uptime()?;
    let memory = info.memory()?;
    let dash_len = user.len() + host.len() + 1;
    
    let result =  [
        "".to_string(),
        format_host(&user, &host),
        draw_dash(dash_len),
        format_info(" os", &os),
        format_info(" kernel", &kernel),
        format_info(" shell", &shell),
        format_info(" uptime", &uptime),
        format_info(" memory", &memory),
    ];

    Some(result)
}

fn format_host(user: &String, host: &String) -> String {
    return format!("{bold}{red}{user}{white}@{bold}{red}{host}", 
        red = RED, 
        user = user, 
        white = WHITE, 
        host = host,
        bold = BOLD,
    );
}

fn draw_dash(len: usize) -> String {
    let mut dash = String::new();
    
    for _i in 0..len {
        dash.push_str("─");
    }

    return format!("{}{}{}", BOLD, WHITE, dash);
}

fn format_info(title: &str, value: &String) -> String {
    return format!("{}{}{}: {}{}", BOLD, GREEN, title, WHITE, value);
}
