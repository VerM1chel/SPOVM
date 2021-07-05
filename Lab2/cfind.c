#include "cfind.h"

int main(int argc, char **argv)
{

    char *path = NULL;
    char *name = NULL;
    char *type = NULL;
    char *user = NULL;
    char *group = NULL;
    char *perm = NULL;

    static struct option l_opt_mass[] = {
        {"name", required_argument, NULL, 'n'}, // Назв поля, нужны обязательные аргументы, NULL => возвращаем val, возвращаемое
        // значение 'n' в переменную, куда указывает flag
        {"type", required_argument, NULL, 't'},
        {"user", required_argument, NULL, 'u'},
        {"group", required_argument, NULL, 'g'},
        {"perm", required_argument, NULL, 'p'},
        {NULL, 0, NULL, 0}};
    if (argc > 1 && argv[1][0] != '-')
    {
        path = argv[1];
        //argc--; // 1 обработали
        //argv++; // ???
    }
    else
    {
        path = (char *)calloc(5, sizeof(char));
        path[0] = '.';
    }

    int opt_index = 1;
    char ch;
    const char *optstring = "w:n:t:u:g:p:";
    do
    {
        ch = getopt_long_only(argc, argv, optstring, l_opt_mass, &opt_index);
        switch (ch)
        {
        case '?':
        {
            printf("Missing option\n");
            exit(-1);
            break;
        };
        case 'n':
        {
            name = optarg; // Указ на строку
            break;
        };
        case 't':
        {
            type = optarg;
            break;
        };
        case 'u':
        {
            user = optarg;
            break;
        };
        case 'g':
        {
            group = optarg;
            break;
        };
        case 'p':
        {
            perm = optarg;
            break;
        };
        }

    } while (ch != -1);

    argc -= optind; // Что обработали
    argv += optind; //Что не обработали
                    //-type тип искомого: f=файл, d=каталог (directory), l=ссылка (link), p=канал (pipe), s=сокет.
    printf("P=%s N=%s T=%s U=%s G=%s P=%s\n", path, name, type, user, group, perm);

    if (type)
    {
        if (!strcmp(type, "f"))
        {
            type_n = 1; //Файл
        }
        else if (!strcmp(type, "d"))
            type_n = 2; //Папка
    }

    char* gid_c=NULL;
    char* uid_c=NULL;
if (user || group)
    {
        uid_c = (char*)calloc(10, sizeof(char));
        gid_c = (char*)calloc(10, sizeof(char));
        char tmp[255];
        sprintf(tmp, "id -u %s >> tmp.txt", user);
        if (user)
        {
            system("echo u=>tmp.txt");
            system(tmp);
        }
        sprintf(tmp, "id -g %s >> tmp.txt", group);
        if (group)
        {
            system("echo g=>>tmp.txt");
            system(tmp);
        }

        int tmpf = open("tmp.txt", O_RDONLY);
        int i = 0, j = 0;
        read(tmpf, tmp, 50);
        while (!isdigit(tmp[i]))
            i++;
        while (isdigit(tmp[i]))
            uid_c[j++] = tmp[i++];
        j = 0;
        while (!isdigit(tmp[i]))
            i++;
        while (isdigit(tmp[i]))
            gid_c[j++] = tmp[i++];
    }
    
    ff(path, name, type, uid_c, gid_c, perm);
    return 1;
}