/*******************************************************************************
 * Copyright 上海赜睿信息科技有限公司(Zilliz) - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited.
 * Proprietary and confidential.
 ******************************************************************************/
#pragma once

#include "db/scheduler/context/SearchContext.h"
#include "db/scheduler/task/IScheduleTask.h"
#include "scheduler/tasklabel/TaskLabel.h"
#include "Path.h"

#include <string>
#include <memory>


namespace zilliz {
namespace milvus {
namespace engine {

enum class LoadType {
    DISK2CPU,
    CPU2GPU,
    GPU2CPU,
};

enum class TaskType {
    SearchTask,
    DeleteTask,
    TestTask,
};

class Task;

using TaskPtr = std::shared_ptr<Task>;

// TODO: re-design
class Task {
public:
    explicit
    Task(TaskType type) : type_(type) {}

    /*
     * Just Getter;
     */
    inline TaskType
    Type() const { return type_; }

    /*
     * Transport path;
     */
    inline Path&
    path() {
        return task_path_;
    }

    /*
     * Getter and Setter;
     */
    inline TaskLabelPtr &
    label() {
        return label_;
    }

public:
    virtual void
    Load(LoadType type, uint8_t device_id) = 0;

    virtual void
    Execute() = 0;

public:
    Path task_path_;
    std::vector<SearchContextPtr> search_contexts_;
    TaskType type_;
    TaskLabelPtr label_ = nullptr;
};


}
}
}
