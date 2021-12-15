use std::{process::Command, fs::read_to_string, env::var};

fn execute_command(command_name: &str, args: Vec<&str>) -> String {
    let mut command = Command::new(command_name);
    command.args(args);

    let output = command.output().expect("Can't execute command");
    return String::from_utf8(output.stdout).unwrap().trim().to_string();
}

pub fn get_host() -> String {
    return execute_command("uname", ["-n"].to_vec());
}

pub fn get_user() -> String {
    return var("USER").expect("Can't fetch $USER env var");
}

pub fn get_os() -> String {
    let file = read_to_string("/etc/os-release").expect("Can't get os release data");

    let line: Vec<&str> = file
        .lines()
        .find(|x| x.contains("NAME"))
        .unwrap()
        .split("=")
        .collect();

    let value = &line[1].trim();
    let os = &value[1..value.len()-1];

    return String::from(os);
}

pub fn get_kernel() -> String {
    return execute_command("uname", ["-r"].to_vec());
}

pub fn get_shell() -> String {
    let shell = var("SHELL").expect("Can't fetch $SHELL env var");

    if shell.is_empty() {
        return String::from("unknown");
    }

    let split: Vec<&str> = shell.split("/").collect();
    let len = split.len();
    return String::from(split[len - 1]);
}

pub fn get_uptime() -> String {
    let uptime = execute_command("uptime", ["-p"].to_vec());
    let sliced = &uptime[3..uptime.len()];
    let formated = sliced
        .replace(" hours", "h")
        .replace(" hour", "h")
        .replace(" minutes", "m")
        .replace(" minute", "m")
        .replace(" days", "d")
        .replace(" day", "d")
        .replace(",", "");

    return String::from(formated);
}

pub fn get_memory() -> String {
    let free_result = execute_command("free", ["-m"].to_vec());
    let lines: Vec<&str> = free_result.lines().collect();
    let mem_line: Vec<&str> = lines[1].split_whitespace().collect();

    return format!("{}m / {}m", mem_line[2], mem_line[1]);
}
