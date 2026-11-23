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

<img width="2340" height="1218" alt="QQ_2026-11-23_09-54-19" src="https://github.com/user-attachments/assets/a42fa4fe-5507-4ee9-b9d9-d10fe1c6ef67" />

<img width="2244" height="1030" alt="QQ_2026-11-23_10-08-35" src="https://github.com/user-attachments/assets/b4df8167-a468-46ac-ba8e-c871f54e7087" />

<img width="2174" height="870" alt="QQ_2026-11-23_10-08-57" src="https://github.com/user-attachments/assets/8070c7b3-1aa9-43e3-8017-89e2a3e1e22d" />

```
public interface RegObserver {
    void handleRegSuccess(long userId);
}

=======================================================

public class RegPromotion implements RegObserver {

    private PromotionService promotionService;

    @Override
    public void handleRegSuccess(long userId) {
        promotionService.issueNewUserExperienceCash(userId);
    }
}

=======================================================

public class CouponObserver implements RegObserver {

    private CouponService couponService;

    @Override
    public void handleRegSuccess(long userId) {
        couponService.issueCoupon(userId);
    }
}

=======================================================

public class RegNotification implements RegObserver {

    private NotificationService notificationService;

    @Override
    public void handleRegSuccess(long userId) {
        notificationService.sendInboxMessage(userId);
    }
}

=======================================================

import java.util.ArrayList;
import java.util.List;

public class UserService {

    private List<RegObserver> observers = new ArrayList<>();

    // 添加观察者
    public void addObserver(RegObserver observer) {
        observers.add(observer);
    }

    // 删除观察者
    public void removeObserver(RegObserver observer) {
        observers.remove(observer);
    }

    // 通知所有观察者
    private void notifyObservers(long userId) {
        for (RegObserver observer : observers) {
            observer.handleRegSuccess(userId);
        }
    }

    public long register(String telephone, String password) {
        // 执行用户注册逻辑，得到 userId
        long userId = saveUser(telephone, password);

        // 注册成功后通知所有观察者
        notifyObservers(userId);

        return userId;
    }

    // 示意方法：具体注册持久化逻辑由原系统实现
    private long saveUser(String telephone, String password) {
        // 校验、加密密码、保存用户等
        throw new UnsupportedOperationException("待实现注册逻辑");
    }
}

=======================================================

public class UserController {

    private UserService userService;

    public Long register(String telephone, String password) {

        return userService.register(telephone, password);
    }
}

=======================================================

UserService userService = new UserService();

userService.addObserver(new RegPromotion());
userService.addObserver(new CouponObserver());
userService.addObserver(new RegNotification());

=======================================================

//假设以后需要增加积分奖励，只需要定义一个新的观察者：
public class PointsObserver implements RegObserver {

    @Override
    public void handleRegSuccess(long userId) {
        System.out.println("给用户发放积分：" + userId);
    }
}

userService.addObserver(new PointsObserver());
```

```
register() {
    注册();
    发放体验金();
    发放优惠券();
    发送消息();
}
变成
register() {
    注册();
    notifyObservers();
}
```

</br>

# 模板方法设计模式

在父类中定义一个算法的执行流程，将其中某些具体步骤交给子类实现。

<img width="2264" height="930" alt="QQ_2026-11-23_10-17-26" src="https://github.com/user-attachments/assets/0214b6ce-c495-4c30-b97d-0e57a83e5064" />

```
abstract class Beverage {

    // 模板方法：规定制作饮料的流程
    public final void prepare() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }

    // 公共步骤
    void boilWater() {
        System.out.println("烧开水");
    }

    void pourInCup() {
        System.out.println("倒入杯中");
    }

    // 不同的步骤交给子类实现
    abstract void brew();

    abstract void addCondiments();
}

class Coffee extends Beverage {

    @Override
    void brew() {
        System.out.println("冲泡咖啡");
    }

    @Override
    void addCondiments() {
        System.out.println("加入牛奶和糖");
    }
}

class Tea extends Beverage {

    @Override
    void brew() {
        System.out.println("浸泡茶叶");
    }

    @Override
    void addCondiments() {
        System.out.println("加入柠檬");
    }
}
```

</br>

# 策略模式

定义一系列算法，将每个算法封装成独立的类，使它们可以相互替换。（把不同的处理方式封装起来，程序可以根据需要选择使用哪一种。）

```
public interface PayStrategy {
    void pay(double money);
}
```

```
public class AliPay implements PayStrategy {

    @Override
    public void pay(double money) {
        System.out.println("支付宝支付：" + money);
    }
}
```

```
public class WeChatPay implements PayStrategy {

    @Override
    public void pay(double money) {
        System.out.println("微信支付：" + money);
    }
}
```

```
public class BankPay implements PayStrategy {

    @Override
    public void pay(double money) {
        System.out.println("银行卡支付：" + money);
    }
}
```

```
public class PaymentContext {

    private PayStrategy strategy;

    // 构造方法注入策略
    public PaymentContext(PayStrategy strategy) {
        this.strategy = strategy;
    }

    // 动态切换策略
    public void setStrategy(PayStrategy strategy) {
        this.strategy = strategy;
    }

    public void pay(double money) {
        strategy.pay(money);
    }
}
```

```
public class Main {

    public static void main(String[] args) {

        PaymentContext context =
                new PaymentContext(new AliPay());

        context.pay(100);

        // 切换为微信支付
        context.setStrategy(new WeChatPay());
        context.pay(200);

        // 切换为银行卡支付
        context.setStrategy(new BankPay());
        context.pay(300);
    }
}
```

<img width="2276" height="1038" alt="QQ_2026-11-23_10-31-31" src="https://github.com/user-attachments/assets/259306ff-e162-4018-a651-97d4ac3857ec" />

<img width="2344" height="424" alt="QQ_2026-11-23_10-34-24" src="https://github.com/user-attachments/assets/9a26fc76-0169-4d3c-b8ba-319e8d3141d1" />

# 责任链设计模式

将多个处理者连接成一条链，请求沿着这条链传递，由链上的处理者决定是否处理该请求，以及是否继续传递。（一个请求经过多个处理者，每个处理者负责自己的部分。）

假设公司有一个请假审批系统：

- 请假 1 天以内：组长审批。

- 请假 3 天以内：经理审批。

- 请假超过 3 天：总经理审批。

责任链模式主要包含两个角色：

- Handler 定义处理请求的方法，并保存下一个处理者

- ConcreteHandler 判断自己能否处理请求，不能处理则传递

<img width="1558" height="648" alt="QQ_2026-11-23_10-38-53" src="https://github.com/user-attachments/assets/233997ae-f084-4706-8d4b-a7afef6e93e9" />

```
abstract class Handler {

    protected Handler next;

    // 设置下一个处理者
    public Handler setNext(Handler next) {
        this.next = next;
        return next;
    }

    // 处理请求
    public abstract void handleRequest(int days);
}
```

```
class TeamLeader extends Handler {

    @Override
    public void handleRequest(int days) {
        if (days <= 1) {
            System.out.println("组长批准请假");
        } else if (next != null) {
            next.handleRequest(days);
        }
    }
}
```

```
class Manager extends Handler {

    @Override
    public void handleRequest(int days) {
        if (days <= 3) {
            System.out.println("经理批准请假");
        } else if (next != null) {
            next.handleRequest(days);
        }
    }
}
```

```
class GeneralManager extends Handler {

    @Override
    public void handleRequest(int days) {
        if (days > 0) {
            System.out.println("总经理批准请假");
        } else {
            System.out.println("请假天数不合法");
        }
    }
}
```

```
public class Main {

    public static void main(String[] args) {

        Handler leader = new TeamLeader();
        Handler manager = new Manager();
        Handler boss = new GeneralManager();

        // 构建责任链
        leader.setNext(manager).setNext(boss);

        // 提交请求
        leader.handleRequest(1);
        leader.handleRequest(2);
        leader.handleRequest(5);
    }
}
```

策略模式：选择谁来做。

责任链模式：沿着链传递，让处理者决定谁来做。































































































































































