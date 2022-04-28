use libfetch::{Info, platform::Platform};

pub struct OSInfo {
    info: Info,
}

impl OSInfo {
    pub fn new() -> Self {
        OSInfo { info: Info::new() }
    }

    pub fn os(&self) -> Option<String> {
        self.info.name()
    }

    pub fn hostname(&self) -> Option<String> {
        self.info.hostname()
    }

    pub fn user(&self) -> Option<String> {
        self.info.user()
    }

    pub fn kernel(&self) -> Option<String> {
        self.info.kernel()
    }

    pub fn memory(&self) -> Option<String> {
        let mem = self.info.memory()?;
        let formatted = format!(
            "{}m / {}m",
            mem.used / 1024,
            mem.total / 1024,
        );

        Some(formatted)
    }

    pub fn uptime(&self) -> Option<String> {
        let uptime = self.info.uptime()?;
        let uptime_duration = std::time::Duration::new(uptime as u64, 0);
        let uptime_formatted = humantime::format_duration(uptime_duration);
        let uptime_str = uptime_formatted.to_string();

        Some(uptime_str)
    }

    pub fn shell(&self) -> Option<String> {
        let shell = self.info.shell()?;
        if shell.is_empty() {
            return Some(String::from("unknown"));
        }

        let split: Vec<&str> = shell.split("/").collect();
        let len = split.len();
        let result = String::from(split[len - 1]);

        Some(result)
    }
}
