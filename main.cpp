#include <iostream>

#define CMD_RESULT_BUF_SIZE 1024

int ExecuteCMD_C(const char *cmd, char *result_) {
    char result[CMD_RESULT_BUF_SIZE] = {0};
    char buf_temp[CMD_RESULT_BUF_SIZE] = {0};
    FILE *ptr = NULL;
    int iRet = -1;

    //popen: 开启子进程，建立管道，并运行指令，'r':从子进程获取结果，'w':向子进程写数据
    if ((ptr = popen(cmd, "r")) != NULL)  //popen
    {
        while (fgets(buf_temp, sizeof(buf_temp), ptr) != NULL) {
            if (strlen(result) + strlen(buf_temp) > CMD_RESULT_BUF_SIZE) {
                printf("shell返回结果超出buffer size，进行截断\n");
                break;
            }
            strcat(result, buf_temp);  //字符串拼接
        }
        strcpy(result_, result);
        pclose(ptr);
        ptr = NULL;
        iRet = 0;  // 处理成功
    } else {
        printf("popen %s error\n", cmd);
        iRet = -1; // 处理失败
    }

    return iRet;
}

int main(int argc, char *argv[]) {
//    char cmd[100] = "ls";
//    system(cmd);
    for (int i = 0; i < argc; i++) {
        printf("%d - args: %s    \n", i, argv[i]);
    }

    char result_[CMD_RESULT_BUF_SIZE];
    ExecuteCMD_C("ps -e|grep test2| grep -v 'grep' | awk '{print $1}'", result_);
//    printf("%s", result_);
    ExecuteCMD_C("ls", result_);
    printf("%s", result_);

    return 0;
}


