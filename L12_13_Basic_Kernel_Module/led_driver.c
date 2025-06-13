#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/device.h>

#define DEVICE_NAME "led_device"
#define CLASS_NAME  "led_class"

static dev_t dev_num; // Số major/minor
static struct cdev led_cdev;
static struct class *led_class;
static struct device *led_device;

static int led_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "LED: Device opened\n");
    return 0;
}

static int led_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "LED: Device released\n");
    return 0;
}

static ssize_t led_write(struct file *file, const char __user *buf, size_t len, loff_t *off)
{
    char kbuf[10]; // Buffer trong kernel
    if (len > sizeof(kbuf) - 1)
        return -EINVAL;

    // Copy dữ liệu từ userspace
    if (copy_from_user(kbuf, buf, len))
        return -EFAULT;

    kbuf[len] = '\0'; // Kết thúc chuỗi

    // Xử lý chuỗi "on" hoặc "off"
    if (strncmp(kbuf, "on", 2) == 0)
        printk(KERN_INFO "LED: turn led on\n");
    else if (strncmp(kbuf, "off", 3) == 0)
        printk(KERN_INFO "LED: turn led off\n");
    else
        printk(KERN_INFO "LED: Invalid command\n");

    return len;
}

static struct file_operations fops = {
    .open = led_open,
    .release = led_release,
    .write = led_write,
};

static int __init led_init(void)
{
    // Cấp phát số major/minor
    if (alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME) < 0) {
        printk(KERN_ERR "LED: Failed to allocate major number\n");
        return -1;
    }

    // Khởi tạo character device
    cdev_init(&led_cdev, &fops);
    if (cdev_add(&led_cdev, dev_num, 1) < 0) {
        unregister_chrdev_region(dev_num, 1);
        printk(KERN_ERR "LED: Failed to add cdev\n");
        return -1;
    }

    // Tạo device class
    led_class = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(led_class)) {
        cdev_del(&led_cdev);
        unregister_chrdev_region(dev_num, 1);
        printk(KERN_ERR "LED: Failed to create class\n");
        return PTR_ERR(led_class);
    }

    // Tạo device file tự động trong /dev
    led_device = device_create(led_class, NULL, dev_num, NULL, DEVICE_NAME);
    if (IS_ERR(led_device)) {
        class_destroy(led_class);
        cdev_del(&led_cdev);
        unregister_chrdev_region(dev_num, 1);
        printk(KERN_ERR "LED: Failed to create device\n");
        return PTR_ERR(led_device);
    }

    printk(KERN_INFO "LED: Driver initialized, Major=%d\n", MAJOR(dev_num));
    return 0;
}

static void __exit led_exit(void)
{
    device_destroy(led_class, dev_num);
    class_destroy(led_class);
    cdev_del(&led_cdev);
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_INFO "LED: Driver unloaded\n");
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Simple LED character device driver");