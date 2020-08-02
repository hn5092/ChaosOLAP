# ChaosOLAP
痛点: 在当前olap百花齐放得年代,没有一个olap能够解决所有问题.当前也有许多框架想统一所有查询入口,但是一半也只是做到了路由功能,并不能混合计算,无法扩展其边界.

design: 
整个design围绕着 olap is storage 来做,任何 olap engine,我都可以把你看成是 storage,每个 storage 使用通用得output formage,链接所有olap组件,并让其发挥自己最大得优点


以下是几个能够想得到得case:
1. ClickHouse + batch(spark)  => 低cost预计算引擎 
预计算方面kylin做的还行,但是kylin有几个致命得缺点:
  a. 为了得到最极致的性能,需要创建多个cuboid,造成存储开销极大,
  b. 如果没有最佳得cuboid,容易造成整个server不可用(压力太大)
如果sql select avg(age), t3.city from (selct max(price), age, id from table where xxx group by age, id) t jion  t3 on t.id = t3.id group by t3.city;
t表可以击中cuboid,但是当没有最优得cuboid的时候,base cuboid会压垮整个服务(id是高基列), 在新的架构里面,我们可以使用部分预计算的表(base cuboid) 利用click house极致单机性能,解决子表计算,然后保存数据到通用存储,spark接下来进行join计算


2. spark + hive =>不通阶段使用不通的引擎进行计算,利用mr稳定和spark快的有点

3. 统一优化入口=> hive 做了mysql pushdown 但是spark没有,spark也得写一份pushdown,每个查询引擎都有自己的一套异构pushdown的方法,都是各自实现,差异也很大,很多客户还得知道各自不同实现的坑,实在是难


