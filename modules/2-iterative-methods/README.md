# Iterative methods

<strong><em>What we know is not much. What we do not know is immense..</em></strong>\
de Laplace, Pierre-Simon (1749 - 1827)

Step 1: By subtraction get an equation for the error driven by the perturbation:

$$
\begin{gathered}
A x=b \\
-(A \widehat{x}=b-E \widehat{x}) \\
A(x-\widehat{x})=E \widehat{x} \\
x-\widehat{x}=A^{-1} E \widehat{x}
\end{gathered}
$$

Step 2: Bound error by RHS:

$$
\|x-\widehat{x}\|=\left\|A^{-1} E \widehat{x}\right\| \leq\left\|A^{-1}\right\| \cdot\|E\| \cdot\|\widehat{x}\|
$$

Step 3: Rearrange to write in terms of relative quantities and condition numbers:

$$
\frac{\|x-\hat{x}\|}{\|\hat{x}\|} \leq \operatorname{cond}(A) \frac{\|E\|}{\|A\|}
$$

Theorem 146 (Effect of Storage Errors in b) Let $A x=b$ and $A \hat{x}=b+f$. Then

$$
\frac{\|x-\hat{x}\|}{\|x\|} \leq \operatorname{cond}(A) \frac{\|f\|}{\|b\|}
$$

Proof. Since $A \hat{x}=A x+f, x-\hat{x}=-A^{-1} f,\|x-\hat{x}\| \leq\left\|A^{-1}\right\|\|f\|=$ $\operatorname{cond}(A) \frac{\|f\|}{\|A\|} \leq \operatorname{cond}(A) \frac{\|f\|}{\|b\|}\|x\|$, because $\|b\| \leq\|A\|\|x\|$.

Remark 147 (Interpretation of $\operatorname{cond}(A)$ ) When $E$ is due to roundoff errors $\|E\| /\|A\|=O$ (machine precision). Then these results say that: cond $(A)$ tells you how many significant digits are
lost (worst case) when solving $A x=b$. As an example, if machine precision carries 7 significant digits, $\|E\| /\|A\|=O\left(10^{-7}\right)$, and if $\operatorname{cond}(A)=10^{5}$ then $\hat{x}$ will have at least $7-5=2$ significant digits.

Other properties of $\operatorname{cond}(A)$ :

- $\operatorname{cond}(A) \geq 1$ and $\operatorname{cond}(I)=1$.
- Scaling $A$ does not influence $\operatorname{cond}(A)$ :

$$
\operatorname{cond}(\alpha A)=\operatorname{cond}(A), \quad \text { for any } \alpha \neq 0
$$

- $\operatorname{cond}(A)$ depends on the norm chosen but usually it is of the same order of magnitude for different norms.
- $\operatorname{cond}(A)$ is not related to $\operatorname{det}(A)$. For example, scaling changes $\operatorname{det}(A)$ but not $\operatorname{cond}(A)$ :

$$
\operatorname{det}(\alpha A)=\alpha^{n} \operatorname{det}(A) \text { but } \operatorname{cond}(\alpha A)=\operatorname{cond}(A)
$$

- If $A$ is symmetric then

$$
\operatorname{cond}_{2}(A)=|\lambda|_{\max } /|\lambda|_{\min }
$$

- If $A$ is symmetric, positive definite and $\|\cdot\|=\|\cdot\|_{2}$, then $\operatorname{cond}(A)$ equals the spectral condition number, $\lambda_{\max } / \lambda_{\min }$

$$
\operatorname{cond}_{2}(A)=\lambda_{\max } / \lambda_{\min }
$$

- $\operatorname{cond}(A)=\operatorname{cond}\left(A^{-1}\right)$.
- We shall see in a later chapter that the error in eigenvalue and eigenvector calculations is also governed by $\operatorname{cond}(A)$.

The most important other result involving $\operatorname{cond}(A)$ is for the perturbed system when there are perturbations in both $A$ and $b$.

## The General Case

Say what you know, do what you must, come what may. -Sonja Kovalevsky, [Motto on her paper "On the Problem of the Rotation of a Solid Body about a Fixed Point."

We show next that the error in

$$
(A+E) \hat{x}=b+f \text { compared to the true system: } A x=b
$$

is also governed by $\operatorname{cond}(A)$. This requires some technical preparation.

Lemma 148 (Spectral localization) For any $N \times N$ matrix $B$ and $\|\cdot\|$ any matrix norm:

$$
|\lambda(B)| \leq\|B\|
$$

Proof. $B \phi=\lambda \phi$. Thus $|\lambda|\|\phi\|=\|B \phi\| \leq\|B\|\|\phi\|$.
This result holds for any matrix norm. Thus, various norms of $A$ can be calculated and the smallest used are an inclusion radius for the eigenvalues of $A$.

Theorem 149 Let $B_{N \times N}$. Then we have
$\lim _{n \rightarrow \infty} B^{n}=0$ if and only if there exists a norm $\|\cdot\|$ with $\|B\|<1$.
Proof. We prove $\|B\|<1 \Rightarrow\left\|B^{n}\right\| \rightarrow 0$. This is easy; The other direction will be proven later ${ }^{6}$. We have that $\left\|B^{2}\right\|=\|B \cdot B\| \leq$

[^0]$\|B\| \cdot\|B\|=\|B\|^{2}$. By induction it follows that $\left\|B^{n}\right\| \leq\|B\|^{n}$ and thus
$$
\left\|B^{n}\right\| \leq\|B\|^{n} \rightarrow 0 \text { as } n \rightarrow \infty
$$

We shall use the following special case of the spectral mapping theorem.

Lemma 150 The eigenvalues of $(I-B)^{-1}$ are $(1-\lambda)^{-1}$ where $\lambda$ is an eigenvalue of $B$.

Proof. Let $B \phi=\lambda \phi$. Then, $\phi-B \phi=\phi-\lambda \phi$ and $(I-B) \phi=$ $(1-\lambda) \phi$. Inverting we see that $(1-\lambda)^{-1}$ is an eigenvalue of $(I-B)^{-1}$. Working backwards (with details left as an exercise) it follows similarly that $(1-\lambda)^{-1}$ an eigenvalue of $(I-B)^{-1}$ implies $\lambda$ is an eigenvalue of $B$.

Theorem 151 (The Neumann Lemma) Let $B_{N \times N}$ be given, with $\|B\|<1$. Then $(I-B)^{-1}$ exists and

$$
(I-B)^{-1}=\lim _{N \rightarrow \infty}\left(\sum_{\ell=0}^{N} B^{\ell}\right)
$$

Proof. IDEA OF PROOF: Just like summing a geometric series:

$$
\begin{aligned}
& S=1+\alpha+\alpha^{2}+\cdots+\alpha^{N} \\
& \frac{\alpha S=\alpha+\cdots+\alpha^{N}+\alpha^{N+1}}{(1-\alpha) S=1-\alpha^{N+1}}
\end{aligned}
$$

To apply this idea, note that since $|\lambda| \leq\|B\|,|\lambda|<1$. Further, $\lambda(I-B)=1-\lambda(B)$ by the spectral mapping theorem ${ }^{7}$. Since

[^1]$|\lambda(B)|<1, \lambda(I-B) \neq 0$ and $(I-B)^{-1}$ exists. We verify that the inverse is as claimed. To begin, note that
$$
(I-B)\left(I+B+\cdots+B^{N}\right)=I-B^{N+1}
$$

Since $B^{N} \rightarrow 0$ as $N \rightarrow \infty$

$$
\begin{aligned}
I & +B+\cdots+B^{N}= \\
=(I-B)^{-1}\left(I-B^{N+1}\right) & =(I-B)^{-1}-(I-B)^{-1} B B^{N} \rightarrow(I-B)^{-1}
\end{aligned}
$$

As an application of the Neumann lemma we have the following.
Corollary 152 (Perturbation Lemma) Suppose $A$ is invertible and $\left\|A^{-1}\right\|\|E\|<1$, then $A+E$ is invertible and

$$
\left\|(A+E)^{-1}\right\| \leq \frac{\left\|A^{-1}\right\|}{1-\left\|A^{-1}\right\|\|E\|}
$$

## Exercise 153 Prove this corollary.

The ingredients are now in place. We give the proof of the general case.

Theorem 154 (The General Case) Let

$$
A x=b, \quad(A+E) \hat{x}=b+f
$$

Assume $A^{-1}$ exists and

$$
\left\|A^{-1}\right\|\|E\|=\operatorname{cond}(A) \frac{\|E\|}{\|A\|}<1
$$

Then

$$
\frac{\|x-\hat{x}\|}{\|x\|} \leq \frac{\operatorname{cond}(A)}{1-\left\|A^{-1}\right\|\|E\|}\left\{\frac{\|E\|}{\|A\|}+\frac{\|f\|}{\|b\|}\right\}
$$

Proof. The proof uses same ideas but is a bit more delicate in the order of steps. First ${ }^{8}$

$$
\begin{aligned}
& A x=b \Longleftrightarrow(A+E) x=b+E x \\
& \frac{(A+E) \hat{x}=b+f}{(A+E) e=E x-f} \\
& e=(A+E)^{-1}(E x-f) \\
&\|e\| \leq\left\|(A+E)^{-1}\right\|(\|E\|\|x\|+\|f\|)
\end{aligned}
$$

Now

$$
A x=b \text { so }\left\{\begin{array}{l}
x=A^{-1} b,\|x\| \leq\left\|A^{-1}\right\|\|b\| \\
\|b\| \leq\|A\|\|x\|, \text { and }\|x\| \geq\|A\|^{-1}\|b\|
\end{array}\right.
$$

Thus,

$$
\begin{aligned}
& \frac{\|e\|}{\|x\|} \leq\left\|(A+E)^{-1}\right\|\left(\|E\| \frac{\|x\|}{\|x\|}+\frac{\|f\|}{\|x\|}\right) \\
& \frac{\|e\|}{\|x\|} \leq\left\|(A+E)^{-1}\right\|(\|E\|+\underbrace{\|A\|}_{\text {factor out this A }} \frac{\|f\|}{\|b\|}) \\
& \frac{\|e\|}{\|x\|} \leq\|A\|\left\|(A+E)^{-1}\right\|\left(\frac{\|E\|}{\|A\|}+\frac{\|f\|}{\|b\|}\right)
\end{aligned}
$$

Finally, rearrange terms after using

$$
\left\|(A+E)^{-1}\right\| \leq \frac{\left\|A^{-1}\right\|}{1-\left\|A^{-1}\right\|\|E\|}
$$

${ }^{8}$ The other natural way to start is to rewrite

$$
\begin{aligned}
A x=b \Longleftrightarrow & (A+E) x=b+E x \\
& \frac{A \hat{x}=b+f}{}-E \hat{x} \\
& e=A^{-1}(f-E \hat{x})
\end{aligned}
$$

Since there are 2 natural starting points, the strategy is to try one and if it fails, figure out why then try the other.

Remark 155 (How big is the RHS?) If $\left\|A^{-1}\right\|\|E\| \ll 1$, we can estimate (e.g. $\frac{1}{1-\alpha} \simeq 1+\alpha$ )

$$
\frac{1}{1-\left\|A^{-1}\right\|\|E\|} \sim 1+\left\|A^{-1}\right\|\|E\|=1+\text { small }
$$

so that up to $O\left(\left\|A^{-1}\right\|\|E\|\right)$ the first order error is governed by $\operatorname{cond}(A)$.

Remark 156 (Non-symmetric matrices.) The spectral condition number can be deceptive for non-symmetric matrices. Since $\|A\| \geq|\lambda(A)|$ for each of the eigenvalues $\lambda(A)$ of $A,\|A\| \geq|\lambda|_{\max }(A)$ and $\left\|A^{-1}\right\| \geq\left|\lambda\left(A^{-1}\right)\right|_{\max }=1 /|\lambda(A)|_{\min }$. We thus have

$$
\operatorname{cond}(A) \geq \frac{|\lambda(A)|_{\max }}{|\lambda(A)|_{\min }}
$$

i.e., spectral condition number $\leq$ condition number. For example, for $A$ and $B$ below, $\operatorname{cond}_{2}(A)=\operatorname{cond}_{2}(B)=O\left(10^{5}\right)$ but we calculate

$$
\begin{aligned}
A= & {\left[\begin{array}{ll}
1 & -1 \\
1 & -1.00001
\end{array}\right] \text {, and } B=\left[\begin{array}{ll}
1 & -1 \\
-1 & 1.00001
\end{array}\right] } \\
& \frac{|\lambda|_{\max }(A)}{|\lambda|_{\min }(A)} \sim 1, \text { while } \frac{|\lambda|_{\max }(B)}{|\lambda|_{\min }(B)} \sim 4 \cdot 10^{5}
\end{aligned}
$$

There are many, other results related to Theorem 154 For example, all the above upper bounds as relative errors can be complemented by lower bounds, such as the following.

Theorem 157 Let $A x=b$. Given $\hat{x}$ let $r=b-A \hat{x}$. Then,

$$
\frac{\|x-\hat{x}\|}{\|x\|} \geq \frac{1}{\operatorname{cond}(A)} \frac{\|r\|}{\|b\|}
$$

Exercise 158 Prove the theorem.
The relative distance of a matrix $A$ to the closest non-invertible matrix is also related to $\operatorname{cond}(A)$. A proof due to Kahan ${ }^{9}$ is presented in Exercise 160

Theorem 159 (Distance to nearest singular matrix) Suppose $A^{-1}$ exists. Then,

$$
\frac{1}{\operatorname{cond}(A)}=\min \left\{\frac{\|A-B\|}{\|A\|}: \operatorname{det}(B)=0\right\}
$$

Exercise 160 Theorem 159 is a remarkable result. One proof due to Kahan depends on ingenious choices of particular vectors and matrices.

1. Show that if $B$ is singular, then

$$
\frac{1}{\operatorname{cond}(A)} \leq \frac{\|A-B\|}{\|A\|}
$$

Hint: If $B$ is singular, there is an $x$ so that $B x=0$ and $(A-B) x=A x$. Hence $\|A-B\| \geq\|(A-B) x\| /\|x\|$.
2. Show that there is a matrix $B$ with

$$
\frac{1}{\operatorname{cond}(A)}=\frac{\|A-B\|}{\|A\|}
$$

Hint: Show that it is possible to choose a vector $y$ so that $\left\|A^{-1} y\right\|=\left\|A^{-1}\right\|\|y\| \neq 0$, set $w=\left(A^{-1} y\right) /\left\|A^{-1} y\right\|^{2}$ and set $B=A-y w^{t} 10$

[^2]
## Example 161 (Perturbations of the right hand side b)

Consider the linear system with exact solution $(1,1)$ :

$$
\begin{aligned}
& 3 x_{1}+4 x_{2}=7 \\
& 5 x_{1}-2 x_{2}=3
\end{aligned}
$$

and let $f=(0.005,-0,009)^{t}$ so the RHS is changed to $b+f=$ $(7.005,2.991)$.
The solution is now

$$
\hat{x}=\left(\begin{array}{ll}
0.999 & 1.002
\end{array}\right)^{t}
$$

Since a small change in the RHS produced a corresponding small change in the solution we have evidence that

$$
\left[\begin{array}{cc}
3 & 4 \\
5 & -2
\end{array}\right]
$$

is well-conditioned.
Now modify the matrix to get the system (with exact solution still $\left.(1,1)^{t}\right)$

$$
\begin{aligned}
& x_{1}+x_{2}=2 \\
& 1.01 x_{1}+x_{2}=2.01
\end{aligned}
$$

This system is ill-conditioned. Indeed, change the RHS a little bit to

$$
b+f=(2.005,2.005)^{t}
$$

The new solution $\hat{x}$ is changed a lot to

$$
\hat{x}=(0,2.005)^{t}
$$

Example 162 (Changes in the Coefficients) Suppose the coefficients of the system (solution $=(1,1)^{t}$ )

$$
\begin{aligned}
& 1 x_{1}+1 x_{2}=2 \\
& 1.01 x_{1}+1 x_{2}=2.01
\end{aligned}
$$

are changed slightly to read

$$
\begin{aligned}
& 1 x_{1}+1 x_{2}=2 \\
& 1.0001 x_{1}+1 x_{2}=2.001
\end{aligned}
$$

Then, the exact solution changes wildly to

$$
\hat{x}=(100,-98)^{t}
$$

We still have a very small residual in the perturbed system

$$
\begin{aligned}
& r_{1}=2-(1 \cdot 100+1 \cdot(-98))=0 \\
& r_{2}=2.001-(1.0001 \cdot 100+1 \cdot(-98))=-0.009
\end{aligned}
$$

Example $163(\operatorname{cond}(\mathrm{A})$ and $\operatorname{det}(\mathrm{A})$ not related) Let $\varepsilon$ denote a small positive number. The matrix $A$ below is ill conditioned and its determinant is \& thus near zero:

$$
\left[\begin{array}{cc}
1 & 1 \\
1+\varepsilon & 1
\end{array}\right]
$$

Rescaling the first row gives

$$
\left[\begin{array}{cc}
\varepsilon^{-1} & \varepsilon^{-1} \\
1+\varepsilon & 1
\end{array}\right]
$$

This matrix for an equivalent linear system has $\operatorname{det}(A)=1$ but $\operatorname{cond}(A)=2 \varepsilon^{-1}\left(\varepsilon^{-1}+1+\varepsilon\right)$ which can be high for $\varepsilon$ small.

To summarize:

- If $\operatorname{cond}(A)=10^{t}$ then at most $t$ significant digits are lost when solving $A x=b$.
- $\operatorname{cond}(A)=\|A\|\left\|A^{-1}\right\|$ is the correct measure of ill-conditioning; in particular, it is scale invariant whereas $\operatorname{det}(A)$ is not.
