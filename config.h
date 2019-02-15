#ifdef DEBUG
static const char* gpio_path[3] = {
	"gpio/16",
	"gpio/20",
	"gpio/21",
};
#else
static const char* gpio_path[3] = {
	"/sys/class/gpio/gpio16/value", 
	"/sys/class/gpio/gpio20/value", 
	"/sys/class/gpio/gpio21/value", 
};
#endif
