#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct {
    char* filename;
    int32_t is_dir;
} file_t;

char* file_name(FILE* pFile) {
    int16_t filelen = 0;
    fseek(pFile, 24, SEEK_CUR);
    fread(&filelen, 2, 1, pFile);
    char* filename = calloc(filelen + 1, sizeof(char));
    fseek(pFile, 16, SEEK_CUR);
    fread(filename, filelen, 1, pFile);
    filename[filelen] = 0;
    return filename;
}

int32_t compare(char* a, char* b, int32_t option) {
    int32_t n = strlen(a);
    int32_t m = strlen(b);
    int32_t a_is_dir = 0, b_is_dir = 0, diff = 0;
    while (diff < n && diff < m && a[diff] == b[diff]) diff++;
    for (int32_t i = diff; i < n; i++) {
        if (a[i] == '/') a_is_dir = 1;
    }
    for (int32_t i = diff; i < m; i++) {
        if (b[i] == '/') b_is_dir = 1;
    }
    if (a_is_dir && !b_is_dir) {
        return 0;
    }
    if (b_is_dir && !a_is_dir) {
        return 1;
    }
    if (strcmp(a, b) > 0) {
        return 1 ^ option;
    } else {
        return 0 ^ option;
    }
}

void substr(char* dest, const char* src, unsigned int start, unsigned int cnt) {
    strncpy(dest, src + start, cnt);
    dest[cnt] = 0;
}

int32_t main(int32_t argc, char* argv[]) {
    int32_t a = 0, c = 0, d = 0, reverse = 0;
    while ((c = getopt(argc, argv, "ad")) != -1) {
        switch (c) {
            case 'd':
                d = 1;
                break;
            case 'a':
                a = 1;
                break;
            case '?':
                break;
            default:
                printf("option: unknown\n");
                break;
        }
    }
    if (d == 1 && a == 1) {
        printf("Error\n");
        return 0;
    }
    if (d == 1) {
        reverse = 1;
    }
    char input[256] = {0};
    strncpy(input, argv[argc - 1], 256);
    FILE* pFile = NULL;
    if (strstr(input, ".zip") == NULL) {
        printf("This is not an zip file\n");
        return 0;
    }
    if ((pFile = fopen(input, "rb")) == NULL) {
        printf("file coule not be open\n");
        return 0;
    }

    int32_t num = 0;
    char** name = malloc(sizeof(char*));
    if (name == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }

    int8_t read = 0;
    while (fread(&read, 1, 1, pFile) == 1) {
        if (read == 0x50) {
            if (fread(&read, 1, 1, pFile) != 1 || read != 0x4B) {
                continue;
            }
            if (fread(&read, 1, 1, pFile) != 1 || read != 0x01) {
                continue;
            }
            if (fread(&read, 1, 1, pFile) != 1 || read != 0x02) {
                continue;
            }

            char* filename = file_name(pFile);
            if (filename == NULL) {
                fprintf(stderr, "Failed to read filename.\n");
                exit(EXIT_FAILURE);
            }

            name[num++] = filename;

            char** new_name = realloc(name, (num + 1) * sizeof(char*));
            if (new_name == NULL) {
                fprintf(stderr, "Failed to reallocate memory.\n");
                exit(EXIT_FAILURE);
            }
            name = new_name;
        }
    }
    for (int32_t i = 0; i < num; i++) {
        for (int32_t j = i + 1; j < num; j++) {
            int32_t value = compare(name[i], name[j], reverse);
            if (value == 1) {
                char* tmp = name[i];
                name[i] = name[j];
                name[j] = tmp;
            }
        }
    }
    for(int32_t i=0;i<num;i++){
        if(name[i][strlen(name[i])-1]=='/'){
            if(i && strlen(name[i-1])>strlen(name[i])){
                char* cur = malloc(strlen(name[i]));
                char* oth = malloc(strlen(name[i]));
                substr(cur, name[i], 0, strlen(name[i]));
                substr(oth, name[i-1], 0, strlen(name[i]));
                if(strcmp(cur,oth)==0){
                    for(int32_t j=i;j+1<num;j++){
                        name[j]=name[j+1];
                    }
                    num--;
                    i--;
                }
                free(cur);
                free(oth);
            }
            if(i+1<num && strlen(name[i+1])>strlen(name[i])){
                char* cur = malloc(strlen(name[i]+1));
                char* oth = malloc(strlen(name[i]+1));
                substr(cur, name[i], 0, strlen(name[i]));
                substr(oth, name[i+1], 0, strlen(name[i]));
                if(strcmp(cur,oth)==0){
                    for(int32_t j=i;j+1<num;j++){
                        name[j]=name[j+1];
                    }
                    num--;
                    i--;
                }
                free(cur);
                free(oth);
            }
        }
    }
    for (int32_t i = 0; i < num; i++) {
        int32_t n = strlen(name[i]);
        for (int32_t j = 0; j < n; j++) {
            int32_t pre_same = 0;
            if (i) {
                int32_t cur_right_slash = j;
                int32_t pre_right_slash = j;
                while (name[i-1][pre_right_slash] != '/' && pre_right_slash < strlen(name[i - 1])) {
                    pre_right_slash++;
                }
                while (name[i][cur_right_slash] != '/' && cur_right_slash < strlen(name[i])) {
                    cur_right_slash++;
                }
                char* cur = malloc(pre_right_slash+1);
                char* pre = malloc(cur_right_slash+1);
                substr(cur, name[i - 1], 0, pre_right_slash);
                substr(pre, name[i], 0, cur_right_slash);
                if (strcmp(cur, pre) == 0) {
                    pre_same = 1;
                }
                free(cur);
                free(pre);
            }

            int32_t print_straight_line = 0;
            if (i + 1 < num) {
                int32_t pre_same = 1;
                for (int32_t k = 0; k < j; k++) {
                    if (name[i][k] != name[i + 1][k]) {
                        pre_same = 0;
                    }
                }

                for (int32_t k = i + 1; k < num; k++) {
                    int32_t cur_right_slash = j;
                    int32_t kth_right_slash = j;
                    while (name[i][cur_right_slash] != '/' && cur_right_slash < strlen(name[i])) {
                        cur_right_slash++;
                    }
                    while (name[k][kth_right_slash] != '/' && kth_right_slash < strlen(name[k])) {
                        kth_right_slash++;
                    }
                    char* cur = malloc(cur_right_slash+1);
                    char* suf = malloc(kth_right_slash+1);
                    substr(cur, name[k], 0, cur_right_slash);
                    substr(suf, name[i], 0, kth_right_slash);
                    if (pre_same && strcmp(cur, suf) != 0) {
                        print_straight_line = 1;
                    }
                    free(cur);
                    free(suf);
                }
            }

            if (!j || name[i][j - 1] == '/') {
                if (!pre_same) {
                    printf("+-- ");
                } else if (print_straight_line) {
                    printf("|   ");
                } else {
                    printf("    ");
                }
            }

            if (pre_same) {
                printf(" ");
            } else {
                printf("%c", name[i][j]);
            }

            if (name[i][j] == '/') {
                if (pre_same) {
                    printf("   ");
                } else {
                    printf(" --");
                }
            }
        }
        printf("\n");
        if (i == num - 1) break;
        for (int32_t j = 0; j < n; j++) {
            int32_t print_straight_line = 0;
            for (int32_t k = i + 1; k < num; k++) {
                int32_t cur_right_slash = j;
                int32_t kth_right_slash = j;
                while (name[i][cur_right_slash] != '/' && cur_right_slash < strlen(name[i])) {
                    cur_right_slash++;
                }
                while (name[k][kth_right_slash] != '/' && kth_right_slash < strlen(name[k])) {
                    kth_right_slash++;
                }
                char* cur = malloc(cur_right_slash+1);
                char* kth = malloc(kth_right_slash+1);
                substr(cur, name[i], 0, cur_right_slash);
                substr(kth, name[k], 0, kth_right_slash);
                int32_t pre_same = 1;
                if(strlen(name[k])<j) {
                    pre_same=0;
                }else{
                    for (int32_t l = 0; l < j; l++) {
                        if (name[i][l] != name[k][l]) {
                            pre_same = 0;
                        }
                    }
                }
                if (pre_same && strcmp(cur, kth) != 0) {
                    print_straight_line = 1;
                }
                free(cur);
                free(kth);
            }

            if (!j || name[i][j - 1] == '/') {
                if (print_straight_line) {
                    printf("|   ");
                    int32_t pre_same = 1;
                    for (int32_t k = 0; k < j; k++) {
                        if (name[i][k] != name[i + 1][k]) {
                            pre_same = 0;
                        }
                    }
                    int32_t suf_same = 1;
                    for (int32_t k = j; k < strlen(name[i]) && k < strlen(name[i + 1]) && name[i][k] != '/'; k++) {
                        if (name[i][k] != name[i + 1][k]) {
                            suf_same = 0;
                        }
                    }
                    if (pre_same && !suf_same) {
                        break;
                    }
                } else {
                    printf("    ");
                }
            }

            printf(" ");
            if (name[i][j] == '/') {
                printf("   ");
            }
        }
        printf("\n");
    }

    fclose(pFile);
    for (int32_t i = 0;i < num;i++) {
        free(name[i]);
    }
    free(name);
    return 0;
}
