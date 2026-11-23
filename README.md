# 观察者模式

观察者模式包含两个主要角色：

1. Subject（被观察者）：维护观察者列表，状态变化时通知它们。

2. Observer（观察者）：接收通知，执行相应的操作。

它们是一种 一对多的依赖关系。

```
interface Observer {
    void update(String message);
}

================================================================

interface Subject {
    void attach(Observer observer);
    void detach(Observer observer);
    void notifyObservers(String message);
}

================================================================

import java.util.ArrayList;
import java.util.List;

class UpMaster implements Subject {
    private List<Observer> observers = new ArrayList<>();

    @Override
    public void attach(Observer observer) {
        observers.add(observer);
    }

    @Override
    public void detach(Observer observer) {
        observers.remove(observer);
    }

    @Override
    public void notifyObservers(String message) {
        for (Observer observer : observers) {
            observer.update(message);
        }
    }

    public void publishVideo(String title) {
        System.out.println("UP主发布了：" + title);
        notifyObservers(title);
    }
}

================================================================

class Fan implements Observer {
    private String name;

    public Fan(String name) {
        this.name = name;
    }

    @Override
    public void update(String message) {
        System.out.println(name + "收到通知：" + message);
    }
}

================================================================

public class Main {
    public static void main(String[] args) {
        UpMaster up = new UpMaster();

        Fan fan1 = new Fan("张三");
        Fan fan2 = new Fan("李四");

        up.attach(fan1);
        up.attach(fan2);

        up.publishVideo("Java设计模式教程");

        up.detach(fan1);

        up.publishVideo("观察者模式详解");
    }
}
```




















































































































































































