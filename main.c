#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <git2.h>


// Uhhh this is a cute banner >w<
void print_banner()
{
    printf("\x1b[38;2;91;206;250m    _____                \n");
    printf("\x1b[38;2;245;169;184m   /  _  \\  __ _________ \n");
    printf("\x1b[38;2;255;255;255m  /  /_\\  \\|  |  \\_  __ \\\n");
    printf("\x1b[38;2;245;169;184m /    |    \\  |  /|  | \\/\n");
    printf("\x1b[38;2;91;206;250m \\____|__  /____/ |__|   \n");
    printf("\x1b[38;2;255;255;255m         \\/              \n\n");
    printf("\x1b[38;2;245;169;184mMade with ❤️  by Luna & Tori\x1b[0m\n\n");
}

// Ooo, we're installing a package! Time to get fancy~ OwO
void install_package(const char *package)
{
    print_banner();

    git_libgit2_init();

    printf("\n\e[0;32m==>\x1b[0m Do you want to check the contents of PKGBUILD? [Y/n]: ");
    char response;
    scanf(" %c", &response);

    // Hmm, let's see if the user is interested in checking the PKGBUILD~ ^-^
    if (response == 'Y' || response == 'y' || response == ' ')
    {
        char packagePath[256];
        snprintf(packagePath, sizeof(packagePath), "%s/.cache/%s", getenv("HOME"), package);

        struct stat st = {0};
        if (stat(packagePath, &st) == -1) {
            mkdir(packagePath, 0700);
        }

        char command[256];
        snprintf(command, sizeof(command), "https://aur.archlinux.org/%s.git", package);

        git_repository *repo;
        git_clone(&repo, command, packagePath, NULL);

        char pkgbuildPath[256];
        snprintf(pkgbuildPath, sizeof(pkgbuildPath), "%s/PKGBUILD", packagePath);
        FILE *pkgbuildFile = fopen(pkgbuildPath, "r");
        if (pkgbuildFile != NULL)
        {
            fclose(pkgbuildFile);

            char lessCommand[1024];
            snprintf(lessCommand, sizeof(lessCommand), "less %s", pkgbuildPath);
            system(lessCommand);
        }
        else
        {
            printf("Unable to open PKGBUILD file.\n");
        }

        char cwd[256];
        getcwd(cwd, sizeof(cwd));

        chdir(packagePath);

        system("makepkg -si --needed");

        chdir(cwd);

        git_repository_free(repo);
    }
    else if (response == 'N' || response == 'n')
    {
        // Aww, it doesn't do anything~ Teehee! >_<"
    }
    else
    {
        printf("Invalid input!\n");
    }

    git_libgit2_shutdown();
}

// Oh nuuuu! The package getting removed >~<
void remove_package(const char *package)
{
    char command[256];
    snprintf(command, sizeof(command), "sudo pacman -R %s", package);
    system(command);
}

// Ooh, let me tell you how to use this amazing program! UwU
void print_usage(const char *program_name)
{
    printf("Usage:\n");
    printf("  %s [-i|-r] package_name\n\n", program_name);
    printf("Options:\n");
    printf("  -i       Install a package from the AUR.\n");
    printf("  -r       Remove a package installed from the AUR.\n");
    printf("  package_name   Name of the package to install or remove.\n");
}

int main(int argc, char *argv[])
{
    // Oh no, something went wrong! >.<
    if (argc != 3)
    {
        fprintf(stderr, "Invalid arguments.\n");
        print_usage(argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-i") == 0)
    {
        install_package(argv[2]);
    }
    else if (strcmp(argv[1], "-r") == 0)
    {
        // Time to remove a package! Bye-bye~ OwO
        remove_package(argv[2]);
    }
    else
    {
        fprintf(stderr, "Unknown option: %s\n", argv[1]);
        print_usage(argv[0]);
        return 0;
    }
}
