# ChaosOLAP
痛点: 在当前olap百花齐放得年代,没有一个olap能够解决所有问题.当前也有许多框架想统一所有查询入口,但是一半也只是做到了路由功能,并不能混合计算,无法扩展其边界.

design: 
整个design围绕着 olap is storage 来做,任何 olap engine,我都可以把你看成是 storage,每个 storage 使用通用得output formage,链接所有olap组件,并让其发挥自己最大得优点


以下是几个能够想得到得case:
1. ClickHouse + batch(spark)  => 低cost预计算引擎 
众所周知,预计算方面kylin做的不错,但是kylin有几个致命得缺点:
  a. 为了得到最极致的性能,需要创建多个cuboid,造成得cost非常大
  b. 
如图 以下执行树: 
