#------------------------------------------------------
# helper functions
#------------------------------------------------------
def vectorAngle2D(vec):
    return atan(vec[1]/vec[0])

def formatLatex(string,replacements):
    for key in replacements:
        string = string.replace(key,replacements[key])
    return string

def partialDiff(expr,variable):
    temp = var('temp')
    return diff(expr.subs({variable:temp}),temp).subs({temp:variable})

@parallel(verbose=True,timeout=60)
def parSimp(a):
    return a.full_simplify()
#------------------------------------------------------

#------------------------------------------------------
# Latex Replacements
#------------------------------------------------------
replacements = {'D[0]\\left(\\theta_{1}\\right)\\left(t\\right)':'\\dot\\theta_1',
                   'D[0]\\left(\\theta_{2}\\right)\\left(t\\right)':'\\dot\\theta_2',
                    'D[0]\\left(y_{2}\\right)\\left(t\\right)':'\\dot y_2',
                    'D[0]\\left(y_{1}\\right)\\left(t\\right)':'\\dot y_1',
                   '\\cos\\left(\\theta_{1}\\left(t\\right)\\right)':'c_1',
                   '\\sin\\left(\\theta_{1}\\left(t\\right)\\right)':'s_1',
                   '\\cos\\left(\\theta_{2}\\left(t\\right)\\right)':'c_2',
                   '\\sin\\left(\\theta_{2}\\left(t\\right)\\right)':'s_2',
               '\\cos\\left(\\theta_{2}\\left(\\theta_{1}\\left(t\\right)\\right)\\right)':'c_2',
               '\\sin\\left(\\theta_{2}\\left(\\theta_{1}\\left(t\\right)\\right)\\right)':'s_2',
               'D[0]\\left(\\theta_{2}\\right)\\left(\\theta_{1}\\left(t\\right)\\right)':'\\dot\\theta_2',
               'D[0, 0]\\left(\\theta_{2}\\right)\\left(\\theta_{1}\\left(t\\right)\\right)':'\\ddot\\theta_2',
               'D[0, 0]\\left(\\theta_{1}\\right)\\left(t\\right)':'\\ddot\\theta_1',
               'D[0]\\left(\\theta_{1}\\right)\\left(t\\right)':'\\dot\\theta_1',
               'D[0]\\left(y_{2}\\right)\\left(\\theta_{1}\\left(t\\right)\\right)':'\\dot{{y_2}}',
               'D[0, 0]\\left(y_{2}\\right)\\left(\\theta_{1}\\left(t\\right)\\right)':'\\ddot{{y_2}}',
               'D[0]\\left(y_{1}\\right)\\left(\\theta_{1}\\left(t\\right)\\right)':'\\dot{{y_1}}',
               'D[0, 0]\\left(y_{1}\\right)\\left(\\theta_{1}\\left(t\\right)\\right)':'\\ddot{{y_1}}',
               'y_{2}\\left(\\theta_{1}\\left(t\\right)\\right)':'y_2',
               'y_{1}\\left(\\theta_{1}\\left(t\\right)\\right)':'y_1'}
#------------------------------------------------------

#------------------------------------------------------
# Measurements
#------------------------------------------------------
if C_USE_DATA:
    if verbose:
        print('----------inputing data----------')
    data = {L[1]:0.127,
            L[2]:0.265,
            L[3]:0.265,
            a[1]:0.006,
            a[2]:0.006,
            d['x']:0.116,
            d['y']:0.033,
            c['x']:0.116,
            c['y']:0.033,
            d[1]:0.005,
            d[2]:0.035,
            d[3]:0.027,
            d[4]:0.027,
            mL[1]:0.15,
            mL[2]:0.20,
            mL[3]:0.20,
            mP[1]:0,
            mP[2]:0,
            mP[3]:0,
            mP[4]:0,
            mP[5]:0,
            mP[6]:0,
            rL[1]:0.016,
            rL[2]:0.016,
            rL[3]:0.016,
            rP[1]:0,
            rP[2]:0,
            rP[3]:0,
            rP[4]:0,
            rP[5]:0,
            rP[6]:0,
            rC[1]:0.40,
            rC[2]:0.60,
            mC[1]:0.8,
            mC[2]:1.0,
            g_0:9.8665}
#------------------------------------------------------


#------------------------------------------------------
# variables definitions
#------------------------------------------------------
#--------------------
# global utils
#--------------------
verbose=True
C_USE_DATA=True
#--------------------
if verbose:
   print('----------defining variables----------')
x = var('x')
torque = var('tau')
g = vector([0,-var('g_0')])
L = {i:var('L_{}'.format(i)) for i in range(1,4)}
a = {i:var('a_{}'.format(i)) for i in range(1,3)}
c = {'x':var('c_x'),'y':var('c_y')}
d = {i:var('d_{}'.format(i)) for i in range(1,5)}
d['x'] = var('d_x')
d['y'] = var('d_y')
theta_1 = var('theta_1')
K(x) = 1/2*(L[1]**2-(d['x']**2+d['y']**2+d[1]**2+d[2]**2+2*(d['x']*d[1]*cos(x)+d['y']*d[1]*sin(x))))
coef_sin(x) = d['x']*d[1]+d[1]*d[2]*cos(x)
coef_cos(x) = d['y']*d[2]+d[1]*d[2]*sin(x)
theta_2(x) = acos((coef_cos(x)*K(x)+sqrt(coef_sin(x)^2+coef_cos(x)^2-K(x)^2))/(coef_sin(x)^2+coef_cos(x)^2))
y_1(x) = -d[3]*sin(x)+sqrt(L[2]**2-(a[1]-d[3]*cos(x))**2)
y_2(x) = -d[4]*sin(x)+sqrt(L[3]**2-(a[2]-d[4]*cos(x))**2)
cmC = {1:vector([0,0]),2:vector([c['x'],c['y']])}
cmP = {1:vector([d[1]*sin(theta_2(theta_1)), d[1]*cos(theta_2(theta_1))]),
       2:cmC[2]+vector([d[1]*cos(theta_1), d[2]*sin(theta_1)]),
       3:vector([d[3]*cos(theta_2(theta_1)), d[3]*sin(theta_2(theta_1))]),
       4:-vector([d[4]*cos(theta_2(theta_1)), d[4]*sin(theta_2(theta_1))]),
       5:vector([a[1],-y_1(theta_2)]),
       6:vector([a[2],-y_2(theta_2)])}
cmL = {1:1/2*(cmP[1]+cmP[2]),
      2:1/2*(cmP[4]+cmP[6]),
      3:1/2*(cmP[3]+cmP[5])}
alphaP = {1:theta_1,
         2:theta_2(theta_1),
         3:theta_2(theta_1),
         4:theta_2(theta_1),
         5:0,
         6:0}
alphaL = {1:vectorAngle2D(cmL[1]),
         2:vectorAngle2D(cmL[2]),
         3:vectorAngle2D(cmL[3])}
alphaC = {1:theta_1,
         2:theta_2(theta_1)}
rL = {i:var('r_L_{}'.format(i)) for i in range(1,len(cmL)+1)}
rP = {i:var('r_P_{}'.format(i)) for i in range(1,len(cmP)+1)}
rC = {i:var('r_C_{}'.format(i)) for i in range(1,len(cmC)+1)}
mP = {i:var('m_P_{}'.format(i)) for i in range(1,len(cmP)+1)}
mL = {i:var('m_L_{}'.format(i)) for i in range(1,len(cmL)+1)}
mC = {i:var('m_C_{}'.format(i)) for i in range(1,len(cmC)+1)}
IP = {i:var('I_P_{}'.format(i)) for i in range(1,len(cmP)+1)}
IL = {i:var('I_L_{}'.format(i)) for i in range(1,len(cmL)+1)}
IC = {i:var('I_C_{}'.format(i)) for i in range(1,len(cmP)+1)}
#------------------------------------------------------

#------------------------------------------------------
# Functions of the system
#------------------------------------------------------
if verbose:
   print('----------computing potential functions----------')
V(theta_1) = sum([mP[i]/2*diff(cmP[i],theta_1)*diff(cmP[i],theta_1) for i in range(1,len(cmP)+1)])
V(theta_1) = V(theta_1) + sum([IP[i]/2*partialDiff(alphaP[i],theta_1)*partialDiff(alphaP[i],theta_1) for i in range(1,len(cmP)+1)])
V(theta_1) = V(theta_1) + sum([mL[i]/2*partialDiff(cmL[i],theta_1)*partialDiff(cmL[i],theta_1) for i in range(1,len(cmL)+1)])
V(theta_1) = V(theta_1) + sum([IL[i]/2*partialDiff(alphaL[i],theta_1)*partialDiff(alphaL[i],theta_1) for i in range(1,len(cmL)+1)])
V(theta_1) = V(theta_1) + sum([IC[i]/2*partialDiff(alphaC[i],theta_1)*partialDiff(alphaC[i],theta_1) for i in range(1,len(cmC)+1)])
U(theta_1) = sum([-mP[i]*cmP[i]*g for i in range(1,len(cmP)+1)])
U(theta_1) = U(theta_1) + sum([-mL[i]*cmL[i]*g for i in range(1,len(cmL)+1)])
U(theta_1) = U(theta_1) + sum([-mC[i]*cmC[i]*g for i in range(1,len(cmC)+1)])
#------------------------------------------------------

# #------------------------------------------------------
# # Equations of motion
# #------------------------------------------------------
# if verbose:
#    print('----------computing equations of motion----------')
# eqm = diff(diff(theta_1,t),t)*2*V(theta_1) + diff(theta_1,t)**2*partialDiff(V(theta_1),theta_1)+partialDiff(U(theta_1),theta_1)
# #------------------------------------------------------

#------------------------------------------------------
# Assumptions and Simplification
#------------------------------------------------------
if verbose:
   print('----------making assumptions----------')
assume(d[3]==d[4])
assume(L[2]==L[3])
assume(mL[2]==mL[3])
assume(mP[1]==mP[2])
assume(mP[2]==mP[3])
assume(mP[3]==mP[4])
assume(IL[2]==IL[3])
assume(cmC[2][0]>0)
assume(cmC[2][1]>0)
assume(a[1]==a[2])
assume(d['x']==cmC[1][0])
assume(d['y']==cmC[1][1])
#------------------------------------------------------

#------------------------------------------------------
# Symbolic Linearization
#------------------------------------------------------
if verbose:
   print('----------computing linear coeficients----------')
#-------------------------
# equilbrium point
#-------------------------
# W = (L[1]**2-(d['x']**2+d['y']**2+d[1]**2+d[2]**2))/2-d['y']*d[2]
# z1 = d['x']*d[1]
# z2 = d[1]*(d['y']+d[2])
# eq_point=(z1*W+z2*sqrt(z2**2+z1**2-W**2))/(z2**2+z1**2)
eq_point = 0
#-------------------------
lin_a = 2*diff(V(theta_1),theta_1).subs(theta_1=eq_point)
lin_c = 2*diff(diff(U(theta_1),theta_1),theta_1).subs(theta_1=eq_point)
lin_b = 0
lin_d = -2*diff(diff(U(theta_1),theta_1),theta_1).subs(theta_1=eq_point)*eq_point
lin_a = lin_a.subs(data)
lin_b = lin_b.subs(data)
lin_c = lin_c.subs(data)
lin_d = lin_d.subs(data)
#------------------------------------------------------

#------------------------------------------------------
# ARE
#------------------------------------------------------
if verbose:
  print('----------computing system model----------')
N = 51
k_t = 243/10000
k_f = 0
k_e = 1/393
Lind = 143/1000/1000
R = 127/100
J = 219/10000/100/100
model_matrix = matrix([
[-R/Lind,k_e/Lind,0],
[N**2*k_t/J/(N**2-lin_a),((lin_b-N**2*k_e)/(N**2-lin_a))/J,lin_c/J/(N**2-lin_a)],
[0,1,0]
])
input_matrix = matrix([
[1/Lind],
[0],
[0]
])
exeogenous_matrix = matrix([
[0],
[lin_d/J/(N**2-lin_a)],
[0]
])
#------------------------------------------------------

#------------------------------------------------------
# transfer functions
#------------------------------------------------------
if verbose:
  print('----------computing transfer functions----------')
s = var('s')
K_p, T_i = var('K_p, T_i')
C(s) = K_p*(1+1/T_i/s)
G(s) = (input_matrix[0,0]*s*(s-model_matrix[0,0]))/(s**3-(model_matrix[0,0]+model_matrix[1,1])*s**2+(model_matrix[0,0]*model_matrix[1,1]-model_matrix[0,1]-model_matrix[1,2])*s+(model_matrix[0,0]*model_matrix[1,2]))
H(s) = simplify(C(s)*G(s)/(1+C(s)*G(s)))
#------------------------------------------------------

#------------------------------------------------------
# Gain calculation
#------------------------------------------------------
if verbose:
  print('----------computing optimal gain----------')
sigma = var('sigma')
E_t(s) = -1/s**2*((1-H(s))*(1-H(-s))+sigma**2*C(s)*C(-s))
# integrate(E_t(s),(s,-i*infinity,i*infinity))
#--------------------------
# construct linear system for optimization
#--------------------------



#------------------------------------------------------
# simplification
#------------------------------------------------------
# if verbose:
#   print('----------attempting simplifications----------')
# eqm = simplify(eqm)
# lin_eqm = simplify(lin_eqm)
# a1 = simplify(a1)
# b1 = simplify(b1)
# c1 = simplify(c1)
# d1 = simplify(d1)
#------------------------------------------------------

#------------------------------------------------------
# Output
#------------------------------------------------------
if verbose:
  print('----------writing output----------')
with open('./Log_Report/dyn_lin_a_latex.tex','w') as archive:
  string = formatLatex(latex(lin_a),replacements)
  # if len(string) > 100000:
  #   archive.write(string[:100000]+'\n')
  #   archive.write(string[100000:])
  # else:
  archive.write(string)
with open('./Log_Report/dyn_lin_c_latex.tex','w') as archive:
  string = formatLatex(latex(lin_c),replacements)
  # if len(string) > 100000:
  #   archive.write(string[:100000]+'\n')
  #   archive.write(string[100000:])
  # else:
  archive.write(string)
with open('./Log_Report/dyn_lin_d_latex.tex','w') as archive:
  string = formatLatex(latex(lin_d),replacements)
  # if len(string) > 100000:
  #   archive.write(string[:100000]+'\n')
  #   archive.write(string[100000:])
  # else:
  archive.write(string)
#------------------------------------------------------

#------------------------------------------------------
# debugging
#------------------------------------------------------

#------------------------------------------------------
