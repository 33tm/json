#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse(char *input, size_t size) {
    for (size_t i = 0; i < size; i++) {
        switch (input[i]) {
            case '{':
                printf("Object start\n");
                break;
            case '}':
                printf("Object end\n");
                break;
            case '[':
                printf("Array start\n");
                break;
            case ']':
                printf("Array end\n");
                break;
            case ':':
                break;
            case ',':
                break;
            case '"': {
                size_t j = i + 1;
                while (input[j] != '"') {
                    if (j == size) {
                        printf("Error: Unterminated string\n");
                        exit(1);
                    }
                    j++;
                }
                char *data = malloc(j - i - 1);
                memcpy(data, input + i + 1, j - i - 1);
                printf("String: %s\n", data);
                free(data);
                i = j;
                break;
            }
            case 't':
                if (memcmp(input + i, "true", 4) != 0) {
                    printf("Error: Invalid token\n");
                    exit(1);
                }
                i += 3;
                printf("True\n");
                break;
            case 'f':
                if (memcmp(input + i, "false", 5) != 0) {
                    printf("Error: Invalid token\n");
                    exit(1);
                }
                i += 4;
                printf("False\n");
                break;
            case 'n':
                if (memcmp(input + i, "null", 4) != 0) {
                    printf("Error: Invalid token\n");
                    exit(1);
                }
                i += 3;
                printf("Null\n");
                break;
            case '-':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': {
                int j = i + 1;
                while (((input[j] >= '0' && input[j] <= '9')
                    || input[j] == '.'
                    || input[j] == 'e'
                    || input[j] == 'E')
                    && j != size) j++;
                char *data = malloc(j - i);
                memcpy(data, input + i, j - i);
                long double number = strtold(data, NULL);
                printf("Number: %Lf\n", number);
                free(data);
                i = j - 1;
                break;
            }
        }
    }
}

int main() {
    // char json[] = "{\"hello\": true, \"world\": [\"earth\", \"mar\", {\"moon\": 82935.8923}]}";
    char json[] = "[\"hello\", \"world\", 123.243, 1245, true, false, null]";
    parse(json, sizeof(json) * sizeof(char));
    return 0;
}