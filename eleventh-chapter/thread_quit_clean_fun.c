//
// Created by 王勇椿 on 2020/9/5.
//
/**
 * 线程清理处理程序，以下三个动作会触发执行线程清理处理程序
 * 1.调用pthread_exit函数
 * 2.响应取消请求
 * 3.用非零execute参数调用pthread_clean_up时
 */




