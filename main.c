#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_banner()
{
    printf("\x1b[38;2;91;206;250m   _____                \n");
    printf("\x1b[38;2;245;169;184m  /  _  \\  __ _________ \n");
    printf("\x1b[38;2;255;255;255m /  /_\\  \\|  |  \\_  __ \\\n");
    printf("\x1b[38;2;245;169;184m/    |    \\  |  /|  | \\/\n");
    printf("\x1b[38;2;91;206;250m\\____|__  /____/ |__|   \n");
    printf("\x1b[38;2;255;255;255m        \\/              \n\n");
    printf("\x1b[38;2;245;169;184m   Made with ❤️ Coronux\x1b[0m\n\n");
}

void install_package(const char *package)
{
    system("clear");
    print_banner();

    char command[256];
    snprintf(command, sizeof(command), "git clone https://aur.archlinux.org/%s.git /tmp/%s", package, package);
    system(command);

    char packagePath[256];
    snprintf(packagePath, sizeof(packagePath), "/tmp/%s", package);
    chdir(packagePath);

    char response;
    printf("\n\e[0;32m==>\x1b[0m Do you want to check the contents of PKGBUILD? [Y/n]: ");
    scanf(" %c", &response);

    if (response == 'Y' || response == 'y' || response == ' ')
    {
        system("less PKGBUILD");
    }
    else if (response == 'N' || response == 'n')
    {
        // It no do anything hehe
    }
    else
    {
        printf("Invalid input!\n");
    }

    system("makepkg -si");

    char *home = getenv("HOME");
    chdir(home);

    sprintf(command, "rm -rf /tmp/aurinstaller/%s", package);
    system(command);
}

void remove_package(const char *package)
{
    system("clear");
    print_banner();
    char command[256];
    sprintf(command, "sudo pacman -R %s", package);
    system(command);
}

void print_usage(const char *program_name)
{
    printf("Usage:\n");
    printf("  %s [-i|-r] package_name\n\n", program_name);
    printf("Options:\n");
    printf("  -i       Install a package from the AUR.\n");
    printf("  -r       Remove a package installed from the AUR.\n");
    printf("  package_name   Name of the package to install or remove.\n");
}

int is_git_installed()
{
    FILE *fp = popen("git --version 2>/dev/null", "r");
    if (fp != NULL)
    {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), fp) != NULL)
        {
            if (strstr(buffer, "git") != NULL)
            {
                pclose(fp);
                return 1;
            }
        }
        pclose(fp);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if (!is_git_installed())
    {
        print_banner();
        printf("Git is not installed. Installing git...\n");
        system("sudo pacman -S git 2>/dev/null");
        printf("Git has been installed successfully.\n\n");
        system("clear");
    }

    if (argc != 3)
    {
        print_banner();
        print_usage(argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-i") == 0)
    {
        install_package(argv[2]);
    }
    else if (strcmp(argv[1], "-r") == 0)
    {
        remove_package(argv[2]);
    }
    else
    {
        print_banner();
        fprintf(stderr, "Unknown option: %s\n", argv[1]);
        print_usage(argv[0]);
        return 1;
    }

    return 0;
}
