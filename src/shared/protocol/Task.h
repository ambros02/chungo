//
// Created by greenman on 11/22/26.
//

#ifndef CHUNGO_TASK_H
#define CHUNGO_TASK_H

typedef enum TaskType
{
    STATUS,
    UPLOAD,
    DOWNLOAD,
    CHECK
} TaskType;

typedef struct Task
{
    TaskType type;
} Task;

#endif //CHUNGO_TASK_H
