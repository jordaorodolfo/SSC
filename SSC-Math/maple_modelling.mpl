!#/env/maple

#------------------------------------------------------
# helper functions
#------------------------------------------------------
getCoef:=proc(expr,var)
	local A:
	return coeff(subs(var=A,expr),A):
end proc:

pdiff:=proc(f,x)
	local var:
	return subs(var=x,diff(subs(x=var,f),var)):
end proc:

vectorAngle2D:=proc(vec)
	return arctan(vec[2]/vec[1]):
end proc:
#------------------------------------------------------

#------------------------------------------------------
# Flags
#------------------------------------------------------
C_SIMPLIFY := false:
#------------------------------------------------------

#------------------------------------------------------
# aliases
#------------------------------------------------------
for i from 1 to 2 do
	dtheta[i] := t->diff(theta[i](t),t):
	ddtheta[i] := t->diff(diff(theta[i](t),t),t):
end do:
#------------------------------------------------------

#------------------------------------------------------
# relational equations
#------------------------------------------------------

K := theta_1->(L[1]^2-(d[x]^2+d[y]^2+d[1]^2+d[2]^2+2*d[x]*d[1]*cos(theta_1)+2*d[y]*d[1]*sin(theta_1)))/2:
b := theta_1->d[y]*d[1]+d[1]*d[2]*sin(theta_1):
a := theta_1->-(d[x]*d[2]+d[1]*d[2]*cos(theta_1)):
theta_2 := theta_1->arccos((a(theta_1)*K(theta_1)+b(theta_1)*sqrt(a(theta_1)^2+b(theta_1)^2-K(theta_1)^2))/(a(theta_1)^2+b(theta_1)^2)):
y_1 := theta_1->d[3]*sin(theta_2(theta_1))+sqrt(L[2]^2-(a[1]-d[3]*cos(theta_2(theta_1))^2)):
y_2 := theta_1->d[4]*sin(theta_2(theta_1))+sqrt(L[2]^2-(a[2]-d[4]*cos(theta_2(theta_1)))^2):
#------------------------------------------------------

#------------------------------------------------------
# all the definitions
#------------------------------------------------------
with(VectorCalculus):
cmC[1] := <0,0>:
cmC[2] := <c[x],c[y]>:
cmP[1] := <d[1]*sin(theta_2(theta_1)),d[1]*cos(theta_2(theta_1))>:
cmP[2] := cmC[2]+<d[1]*cos(theta_1),d[2]*sin(theta_1)>:
cmP[3] := <d[3]*cos(theta_2(theta_1)),d[3]*sin(theta_2(theta_1))>:
cmP[4] := <-d[4]*cos(theta_2(theta_1)),-d[4]*sin(theta_2(theta_1))>:
cmP[5] := Vector([a[1],-y_1(theta_2)],2):
cmP[6] := Vector([a[2],-y_2(theta_2)],2):
cmL[1] := 1/2*(cmP[1]+cmP[2]):
cmL[2] := 1/2*(cmP[4]+cmP[6]):
cmL[3] := 1/2*(cmP[3]+cmP[5]):
alphaC[1] := theta_1:
alphaC[2] := theta_2(theta_1):
alphaP[1] := theta_1:
alphaP[2] := theta_2(theta_1):
alphaP[3] := theta_2(theta_1):
alphaP[4] := theta_2(theta_1):
alphaP[5] := 0:
alphaP[6] := 0:
alphaL[1] := vectorAngle2D(cmL[1]):
alphaL[2] := vectorAngle2D(cmL[2]):
alphaL[3] := vectorAngle2D(cmL[3]):
g:=<0,-G>:
#------------------------------------------------------

#------------------------------------------------------
#get the Lagrangian
#------------------------------------------------------
V :=theta_1->add(m[P,i]/2*DotProduct(diff(cmP[i],theta_1),diff(cmP[i],theta_1)),i=1..numelems(cmP)) +
	add(m[L,i]/2*DotProduct(diff(cmL[i],theta_1),diff(cmL[i],theta_1)),i=1..numelems(cmL)) +
	add(I[P,i]/2*diff(alphaP[i],theta_1)^2,i=1..numelems(cmP)) +
	add(I[L,i]/2*diff(alphaL[i],theta_1)^2,i=1..numelems(cmL)) +
	add(I[C,i]/2*diff(alphaC[i],theta_1)^2,i=1..numelems(cmC)):
U :=theta_1->add(-m[P,i]*DotProduct(cmP[i],g),i=1..numelems(cmP)) +
	add(-m[L,i]*DotProduct(cmL[i],g),i=1..numelems(cmL)) +
	add(-m[C,i]*DotProduct(cmC[i],g),i=1..numelems(cmC)):
#------------------------------------------------------

#------------------------------------------------------
#equation of motion
#------------------------------------------------------
eqm:=-diff(diff(theta_1(t),t),t)*2*V(theta_1)
	-diff(theta_1(t),t)^2*diff(V(theta_1),theta_1)
	-diff(U(theta_1),theta_1);
#------------------------------------------------------

#------------------------------------------------------
#assuming a lot of things to make it easier
#------------------------------------------------------
assume(t>0):
assume(d[3] = d[4]):
assume(L[2] = L[3]):
assume(c[x]>0):
assume(c[y]>0):
assume(a[2] = a[1]):
#------------------------------------------------------

#------------------------------------------------------
# measurements
#------------------------------------------------------
data := [L[1]=0.127,
				L[2]=0.265,
				L[3]=0.265,
				a[1]=0.006,
				a[2]=0.006,
				d[x]=0.0116,
				d[y]=0.0033,
				c[x]=0.0116,
				c[y]=0.0033,
				d[1]=0.005,
				d[2]=0.035,
				d[3]=0.027,
				d[4]=0.027,
				m[L,1]=0.15,
				m[L,2]=0.20,
				m[L,3]=0.20,
				m[P,1]=0,
				m[P,2]=0,
				m[P,3]=0,
				m[P,4]=0,
				m[P,5]=0,
				m[P,6]=0,
				L[1]=0.016,
				L[2]=0.016,
				L[3]=0.016,
				rP[1]=0,
				rP[2]=0,
				rP[3]=0,
				rP[4]=0,
				rP[5]=0,
				rP[6]=0,
				rC[1]=0.40,
				rC[2]=0.60,
				I[P,1]=0,
				I[P,2]=0,
				I[P,3]=0,
				I[P,4]=0,
				I[P,5]=0,
				I[P,6]=0,
				I[L,1]=0.15*(0.0.016)^2,
				I[L,2]=0.20*(0.0.016)^2,
				I[L,3]=0.20*(0.0.016)^2,
				I[C,1]=0.8*(0.4)^2,
				I[C,2]=1.0*(0.6)^2,
				G=9.8665
				]:
#------------------------------------------------------

#------------------------------------------------------
# linearization
#------------------------------------------------------
#-------------------------
# equilbrium point
#-------------------------
W := (L[1]^2-(d[x]^2+d[y]^2+d[1]^2+d[2]^2))/2+d[y]*d[2]:
z1 := d[x]*d[1]:
z2 := d[1]*(d[y]-d[2]):
print(simplify(z2^2+z1^2<W^2)):
eq_point := arccos((z1*W+z2*sqrt(z2^2+z1^2-W^2))/(z2^2+z1^2)):
print(subs(data,eq_point)):
#-------------------------
a1 :=-(V(theta_1)*diff(diff(U(theta_1),theta_1),theta_1)-diff(V(theta_1),theta_1)*diff(U(theta_1),theta_1))/(2*V(theta_1)):
a1 := evalf(subs(data,subs(theta_1=eq_point,a1)));
b1 := 0:
c1 := evalf(-a1*subs(data,eq_point)):
d1 := a1+b1:
#------------------------------------------------------

#------------------------------------------------------
# simplify
#------------------------------------------------------
if C_SIMPLIFY then
	eqm := simplify(eqm):
end if:
#------------------------------------------------------

#------------------------------------------------------
# output
#------------------------------------------------------
FileTools[Remove]("./Log_Report/dyn_eqm_latex.tex"):
latex(eval(subs(data,eqm)),"./Log_Report/dyn_eqm_latex.tex"):
FileTools[Remove]("./Log_Report/dyn_a1_latex.tex"):
latex(eval(subs(data,a1)),"./Log_Report/dyn_a1_latex.tex"):
FileTools[Remove]("./Log_Report/dyn_b1_latex.tex"):
latex(eval(subs(data,b1)),"./Log_Report/dyn_b1_latex.tex"):
FileTools[Remove]("./Log_Report/dyn_c1_latex.tex"):
latex(eval(subs(data,c1)),"./Log_Report/dyn_c1_latex.tex"):
FileTools[Remove]("./Log_Report/dyn_d1_latex.tex"):
latex(eval(subs(data,d1)),"./Log_Report/dyn_d1_latex.tex"):
#------------------------------------------------------
