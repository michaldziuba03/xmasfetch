use std::{process::Command, fs::read_to_string, env::var};
#[cfg(target_os = "freebsd")]
use std::time::{SystemTime, UNIX_EPOCH};

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
    let os = &value.replace('"', "");

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

#[cfg(target_os = "linux")]
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

#[cfg(target_os = "freebsd")]
fn get_now() -> u64 {
    let start = SystemTime::now();
    let duration = start.duration_since(UNIX_EPOCH).expect("cannot get current timestamp");

    return duration.as_secs();
}

#[cfg(target_os = "freebsd")]
pub fn get_uptime() -> String {
    let uptime_result = execute_command("sysctl", ["-n", "kern.boottime"].to_vec());

    let split_one: Vec<&str> = uptime_result.split("=").collect();
    let split_two: Vec<&str> = split_one[1].trim().split(",").collect();

    let uptime: u64 = split_two[0].parse().unwrap();
    let now = get_now();

    let result = now - uptime;
    if result < 60 {
        return format!("{}s", result);
    }

    if result > 60 && result < 3600 {
        return format!("{}m", result / 60);
    }

    let hours = result / 3600;
    let minutes = result / 60 - hours * 60;

    return format!("{}h {}m", hours, minutes);
}

#[cfg(target_os = "linux")]
pub fn get_memory() -> String {
    let free_result = execute_command("free", ["-m"].to_vec());
    let lines: Vec<&str> = free_result.lines().collect();
    let mem_line: Vec<&str> = lines[1].split_whitespace().collect();

    return format!("{}m / {}m", mem_line[2], mem_line[1]);
}

#[cfg(target_os = "freebsd")]
pub fn ask_sysctl(arg: &str) -> u64 {
    let result: u64 = execute_command("sysctl", ["-n", arg].to_vec())
        .trim()
        .parse()
        .unwrap();

    return result;
}

#[cfg(target_os = "freebsd")]
pub fn get_memory() -> String {
    let pagesize = ask_sysctl("hw.pagesize");
    let mem_inactive = ask_sysctl("vm.stats.vm.v_inactive_count");
    let mem_unused = ask_sysctl("vm.stats.vm.v_free_count");
    let mem_cache = ask_sysctl("vm.stats.vm.v_cache_count");

    let mem_total = ask_sysctl("hw.physmem") / 1024 / 1024;
    let mem_free = (mem_inactive + mem_unused + mem_cache) * pagesize / 1024 / 1024;

    return format!("{}m / {}m", mem_total, mem_total - mem_free);
}