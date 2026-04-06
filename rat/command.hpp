#include <cstdlib>
#include <format>
#include <string>

template<typename... Args>
inline int runCommand(std::format_string<Args...> fmt, Args&&... args) {
	std::string cmd = std::format(fmt, std::forward<Args&&>(args)...);
	return system(cmd.c_str());
}
