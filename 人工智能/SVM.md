<script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=default"></script>

# SVM(Support Vector Machine)

**支持向量机（Support Vector Machine, SVM）**是一类按监督学习方式对数据进行二元分类的广义线性分类器。通过**核技巧**，还可以使它成为非线性分类器。

## 基本原理

### 建模

已知一个**线性可分**的数据集:
$$
T=\{(x_1,y_1),(x_2,y_2),\cdots,(x_n,y_n)\}，其中x_i\in \R^{n},y_i\in \{-1,+1\}
$$
**划分准则**:
​        希望找到一个**超平面**（$w^\mathrm{T}\cdot x+b=0$），使超平面处于$T$中的两类点的“正中间”，距离超平面最近的点称为**支持向量（support vector）**，要求**margin（两边支持向量到超平面的距离之和）**尽可能大（这样容错率更高）。

<center class="half">
<img src="D:\NetworkFile\数据挖掘\exp\exp2\SVM.assets\smallmargin.png" width="250"/>
<img src="D:\NetworkFile\数据挖掘\exp\exp2\SVM.assets\largemargin.png" width="250"/>
</center>
**几何间隔(点到超平面的距离)**[\[1]](#1)：
$$
\gamma_i=\frac{1}{\Vert w\Vert_2}\vert w^\mathrm{T}x_i+b\vert
=\frac{y_i(w^\mathrm{T}x_i+b)}{\Vert w\Vert_2}
$$
要求margin尽可能大，即求解以下最优化问题：
$$
\arg\max_{w,b}\min_{n} \frac{y_i(w^\mathrm{T}x_i+b)}{\Vert w\Vert_2}
$$
又可以写成：
$$
\begin{align*}&\max_{w,b}\quad \frac{\hat{\gamma}}{\Vert w\Vert_2} \\ &\text{s.t.} \quad y_i(w^\mathrm{T}x_i+b) \ge \hat{\gamma}\end{align*}
$$

* 若该最优化问题有解（一定有），则会有无数个等价的解，因为等比例增大$w,b$，仍然表示同一个超平面，而且几何间隔并不会改变。因此不妨取$\hat{\gamma}=1$来方便计算。

* $\max\frac{1}{\Vert w\Vert} \Leftrightarrow \min \Vert w\Vert \Leftrightarrow \min \frac{1}{2}\Vert w\Vert^{2}$（此处及下文中出现的范数都默认是第二范数）

则问题化简为（出现平方和1/2是为了方便后面计算）：

$$
\begin{align*}&\min_{w,b} \quad \frac{1}{2}\Vert w\Vert^{2} \\ &\text{s.t.} \quad 1-y_i(w^\mathrm{T}\cdot x_i+b) \le 0 \end{align*}
$$

### 问题求解

这是一个凸优化问题，可以用拉格朗日对偶函数[\[2]](#2)进行求解：
$$
L(w,b,\alpha)=\frac{1}{2}\Vert w\Vert^{2}-\sum^{n}\alpha_i[y_i(w^\mathrm{T}\cdot x_i+b)-1]，其中\alpha_i\ge0
$$

## 补充定理

### <span id="1">点到超平面的距离</span>

对于二维空间，点$(x_i,y_i)$到直线$ax+by+c=0$的距离公式为：
$$
d=\frac{\vert ax_i+by_i+c\vert}{\sqrt{a^2+b^2}}
$$
推广到$\R^n$，有：
$$
d=\frac{\vert w^{\mathrm T}x+b\vert}{\Vert w\Vert_2}
$$
证明一：

假设点$x$在超平面上的投影为$x_0$，则有$w^{\mathrm T}x_0+b=0.$

因为$\overrightarrow {xx_0}$与超平面的法向量$w$平行，因此有：
$$
\vert w\cdot \overrightarrow{xx_0}\vert=\vert w\vert \vert \overrightarrow {xx_0}\vert \\ 
其中\vert w\vert=\Vert w\Vert_2,\quad\vert \overrightarrow {xx_0}\vert=d \\ 
\begin{align*}
w\cdot \overrightarrow{xx_0}&=\sum_{i=1}^{n} w_i(x_i-x_{0i})=\sum_{i=1}^{n} w_ix_i-\sum_{i=1}^{n} w_ix_{0i}\\&=w^{\mathrm T}x-w^{\mathrm T}x_0=w^{\mathrm T}x +b
\end{align*}
$$
代入化简，证毕：
$$
\vert w^{\mathrm T}x+b\vert=\Vert w\Vert_2d
$$
证明二：

已知$w$为超平面的法向量，设$x_1$为超平面上的任意一点，有$w^{\mathrm T}\cdot x_1+b=0$，则：
$$
d=\vert x-x_1\vert\cos{\theta}=\vert x-x_1\vert \frac{\vert w\cdot (x-x_1)\vert}{\vert w\vert \vert x-x_1\vert}=\frac{\vert w^{\mathrm T}x+b\vert}{\Vert w\Vert_2}
$$

### <span id="2">拉格朗日对偶问题</span>

#### 原始问题(Primal problem)

考虑以下约束最优化问题：
$$
\left\{
\begin{gather*}
&\min {f(x)},\\
\text{s.t.}&h_i(x)=0,\quad i=1,2,\cdots,p\\
&g_j(x)\le0,\quad j=1,2,\cdots,q
\end{gather*}
\right.
$$
构造拉格朗日函数有：
$$
L(x,\lambda,\mu)=f(x)+\sum_{i=1}^{p}{\lambda_i h_i(x)}+\sum_{j=1}^{q}{\mu_j g_j(x)}
$$
#### 对偶问题(Dual problem)

由于$f(x)$的凹凸性未知，即使求出局部最优点（极值点），也不确定其是否是全局最优点。因此考虑其对偶问题：

$$
\left\{
\begin{gather*}
\max_{\lambda,\mu} {\theta_d(\lambda,\mu)}=
\max_{\lambda,\mu} {\min_x {L(x,\lambda,\mu)}}\\
\text{s.t.}\quad \mu_i\ge0,\quad i=1,2,\cdots,q
\end{gather*}
\right.
$$
记$\theta_d(\lambda,\mu)=\min_x {L(x,\lambda,\mu)}$为**拉格朗日对偶函数**，它一定是凹函数。

证明：

为了方便书写，记$\gamma=(\lambda,\mu)$，则$\theta_d(\lambda,\mu)=\theta_d(\gamma)=min_x {L(x,\gamma)}.$

根据凹函数的定义有：
$$
\begin{aligned}
\theta_d[\alpha\gamma_1+(1-\alpha)\gamma_2]&=\min_x {L(x,\alpha\gamma_1+(1-\alpha)\gamma_2)}\\
&= \min_x {{[\alpha L(x,\gamma_1)+ (1-\alpha)L(x,\gamma_2)]}}\\
&\ge \alpha\min_x {L(x,\gamma_1)}+(1-\alpha)\min_x {L(x,\gamma_2)}\\
&= \alpha \theta_d(\gamma_1)+(1-\alpha)\theta_d(\gamma_2)
\end{aligned}\\
$$

* 第一步到第二步：

  $\theta_d$是关于$\gamma$的函数，因此在$L(x,\gamma)$中$x$是固定的，即$f(x),h_i(x),g_j(x)$都是常数，记为$r,p,q$，有：
  $$
  L(x,\gamma)=\sum {\lambda_ip_i}+\sum {\mu_jq_j}+r
  $$
  显然，$L(x,\gamma)$是一个**仿射函数（$f:\R^n\rightarrow \R^m,x\rightarrow Ax+b$）**，根据仿射函数**即凸又凹**的性质有（写成$\ge$也可以）：
  $$
  L(x,\alpha\gamma1+(1+\alpha)\gamma_2)=\alpha L(x,\gamma_1)+(1-\alpha)L(x,\gamma_2)
  $$

* 第二步到第三步：

  用到了$min$函数的性质：
  $$
   \min{(x+y)}\ge\min {x}+\min {y}\quad(x,y\in\R^n)
  $$
   证明：
  $$
  \begin{align*}
   \left.\begin{aligned}
   x_i\ge\min{x}\\
   y_i\ge\min{y} 
   \end{aligned}\right\}
   &\Rightarrow x_i+y_i\ge \min{x}+\min{y}\\
   &\Rightarrow \min{(x_i+y_i)}\ge \min {(\min {x}+\min {y})}\\
   &\Rightarrow \min{(x+y)}\ge\min {x}+\min {y}\\
   \end{align*}
  $$

#### 对偶问题与原始问题的关系

把原始问题和对偶问题记为$p,d$，相应的最优解记为$p^*,d^*$，有：
$$
\left.\begin{align*}\mu_j\ge0\\g_j(x)\le0\end{align*}\right\}
\Rightarrow\sum_{j=1}^{q}{\mu_j g_j(x)}\le0\\\Rightarrow
\theta_d(\lambda,\mu)\le L(x,\lambda,\mu)\le f(x) \\\Rightarrow
d^*=\theta_d(\lambda^*,\mu^*)
\le 
f(x^*)=p^*\\\Leftrightarrow
d^*\le p^*
$$

上述性质被称为**弱对偶性(weak duality)**，是原始问题与对偶问题必定存在的性质。

回顾上面的过程：

* $p^*$凹凸性未知，比较难求解，一通操作原地踏步
* $\theta_d(\lambda,\mu)$是一个凹函数，$d^*$比较容易求解
* $d^*\le p^*$，即对偶问题的最优解是原始问题最优解的下界

因此希望通过求解$d^*$来逼近$p^*$，而$d^*=p^*$的情况被称为**强对偶性（strong duality）**。

#### 强对偶性和最优解成立的条件

##### 凸优化问题

对于一般的最优化问题：
$$
\left\{
\begin{gather*}
&\min {f(x)},\\
\text{s.t.}&h_i(x)=0,\quad i=1,2,\cdots,p\\
&g_j(x)\le0,\quad j=1,2,\cdots,q
\end{gather*}
\right.
$$

> 如果最优化问题满足：
> * $f(x)$是凸函数
>
> * $g(x)$是凸函数
>
> * $h(x)$是仿射函数
>
> 则该问题是一个**凸优化问题(Convex optimization problem)**。

##### Slater条件:

$$
\exist x\in relint(D)\text{（定义域相对内部）}\\
\begin{align*}
\text{s.t.} \quad&h_i(x)=0,\quad i=1,2,\cdots,p\\
&g_i(x)<0,\quad j=1,2,\cdots,q
\end{align*}
$$

> 如果：
>
> * 原始问题是**凸优化问题**
>
> * 原始问题满足**Slater条件（即约束条件严格成立）**
>
> 则原始问题和对偶问题是强对偶的。

证明参考：[1](http://www.ifp.illinois.edu/~angelia/L8_strongdthms.pdf#page=4), [2](https://www.ece.nus.edu.sg/stfpage/vtan/ee5138/slater.pdf).

##### KKT(Karush-Kuth-Tucker)条件

若$x^*$为局部最优解，则$x^*$满足：
$$
\left\{
\begin{gather*}
\nabla{f(x^*)}+\sum{\lambda_i\nabla{h_i(x^*)}}+\sum{\mu_j\nabla{g_j(x^*)}}=0,\\
h_i(x^*)=0,\quad i=1,2,\cdots,p\\
g_j(x^*)\le0,\quad j=1,2,\cdots,q\\
\mu_j\ge0,\quad j=1,2,\cdots,q\\
\mu_jg_j(x^*)=0,\quad j=1,2,\cdots,q
\end{gather*}
\right.
$$

* **Stationarity（平稳性）**，极值点处偏导数为0。

* **Primal feasibility（原问题约束）**

* **同上**

* **Primal feasibility（对偶问题约束，对偶松弛）**。$\mu_j$又叫**KKT乘子**，结合第一点和第五点，有：
  $$
  -\nabla f(x^*)=\sum {\lambda_i\nabla {h_i(x^*)}}+\sum {\mu_j\nabla g_j(x^*)},\quad
  \left\{\begin{align*}
  \mu_j=0,\quad g_j(x^*)<0\\
  \mu_j\ge0,\quad g_j(x^*)=0
  \end{align*}\right.
  $$
  设$T_\Omega(x^*)$是$x^*$在约束集$\Omega$中的可行方向的集合，称为$\Omega$在$x^*$处的**切锥（Tangent cone）**；设$N_\Omega(x^*)$是与所有可行方向成钝角的方向集合，称为**法锥（Normal cone）**。当$x^*$是局部最优解时，有$-\nabla f(x^*)\in N_\Omega(x^*)$，即任一可行方向都不能是$f(x)$的下降方向，否则$x^*$不是局部最优解。而$N_\Omega(x^*)$正好是相关约束面$h,g$在$x^*$处的外法向量生成的凸锥，即$N_\Omega(x^*)=\{\sum{\lambda_ih_i(x^*)}+\sum{\mu_jg_j(x^*)}|\lambda_i\in\R,\mu_i\ge0\}$。参考：[1](https://www.zhihu.com/question/23311674/answer/1176688432).

* **Complementary slackness（互补松弛性）**，如果对应某一约束条件的对偶变量为非零 ， 则该约束条件取严格等式 ； 反之 ， 当约束条件取严格不等式时 ， 则其对应的对偶变量一定为0。参考：[1](https://www.matem.unam.mx/~omar/math340/comp-slack.html).

> 对于一般性的优化问题，如果：
>
> > * $x^*$是问题的局部最优解
> >
> > $\Rightarrow x^*$满足KKT条件
>
>  对于可微分凸优化问题：
>
> > 
> > * 如果$\exist x^*$满足KKT条件
> >
> > $\Rightarrow$强对偶成立，且$x^*$是全局最优解