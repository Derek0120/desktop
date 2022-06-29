#pragma once
#include "base/include/base_global.h"
#include "common/include/logger.h"
#include "common/include/concurrent/TaskScheduler.h"
#include "common/include/concurrent/Task.h"
#include <QCoreApplication>
namespace base{
    namespace internal{
class TaskEvent : public QEvent{
public:
    using QEvent::QEvent;
    common::Task task;
};

class MainObject : public QObject{
    Q_OBJECT
public:
    using QObject::QObject;
    enum  {
        TaskType = QEvent::User + 1
    };
    bool event(QEvent *e){
        if((int)e->type() == (int)TaskType){
            TaskEvent* ptr = dynamic_cast<TaskEvent*>(e);
            if(ptr){
                ptr->task.exec();
            }
            return true;
        }
        return QObject::event(e);
    }
};

class MainThreadSchedulerImpl : public common::ITaskScheduler
{
public:
    MainThreadSchedulerImpl(){
        mainObject = new MainObject;
    }
    ~MainThreadSchedulerImpl(){
        delete mainObject;
    }

    void postTask(const common::Task& task) override{
        TaskEvent* event = new TaskEvent((QEvent::Type)MainObject::TaskType);
        event->task = task;
        qApp->postEvent(mainObject, event);
    }

	bool start()override {
        stopped_ = false;
       int ret = qApp->exec();
       stopped_ = true;
       return 0 == ret;
    }

	bool stop() override{
        qApp->quit();
        return true;
    }
     bool stopped() const override{
         return stopped_;
     }

     private:
     QObject* mainObject;
     bool stopped_ {true};
};

}
}