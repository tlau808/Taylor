import itertools
import math
import time
import re

def nCr(n,r):
    f = math.factorial
    return f(n) / f(r) / f(n-r)

def sumDigits(n):
    s = 0
    while n:
        s += n % 10
        n //= 10
    return s

def sumOfDivisors(stop):
    sd=[0 for i in range(stop)]
    for divisor in range(1,math.ceil(stop/2)):
       k=2
       while k*divisor<stop:
           sd[k*divisor]+=divisor
           k+=1
    return sd

# primitive
def isPrime(n):
    if n <= 0:
        return False
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            return False
    return True

# return all primes up to n
def sieve(n):
	izip = itertools.zip_longest
	chain = itertools.chain.from_iterable
	compress = itertools.compress
	zero = bytearray([False])
	size = n//3 + (n % 6 == 2)
	sieve = bytearray([True]) * size
	sieve[0] = False
	for i in range(int(n**0.5)//3+1):
		if sieve[i]:
		    k=3*i+1|1
		    start = (k*k+4*k-2*k*(i&1))//3
		    sieve[(k*k)//3::2*k]=zero*((size - (k*k)//3 - 1) // (2 * k) + 1)
		    sieve[  start ::2*k]=zero*((size -   start  - 1) // (2 * k) + 1)
	ans = [2,3]
	poss = chain(izip(*[range(i, n, 6) for i in (1,5)]))
	ans.extend(compress(poss, sieve))
	return ans


def euler1():
	total=0
	for i in range(1,1000):
		if i%3==0 or i%5==0:
			total+=i
	return total

def euler2():
	total, a, b, c = 0, 1, 1, 2
	while c < 4000000:
		total += c # only add every third number
		a=b+c
		b=c+a
		c=a+b
	return total

def euler3():
	# factorize via Wolfram Alpha
	return 6857

def euler4():
	maxPalindrome = 0
	for i in range(100, 1000):
		for j in range(100, 1000):
			product = i*j
			if (product > maxPalindrome):
				productString = str(product)
				if (productString == productString[::-1]):
					maxPalindrome = product
	return maxPalindrome

def euler5():
	x = 1
	for i in range(2, 21):
		x = int(x*i/math.gcd(x, i)) # LCM(x, y)*GCD(x, y) = xy
	return x
	
def euler6():
	s = 100*(100+1)/2 # linear sum
	sq = (2*100+1)*(100+1)*100/6 # sum of squares
	return s*s-sq

def euler7():
	return sieve(200000)[10000]

def euler8():
	n = "7316717653133062491922511967442657474235534919493496983520312774506326239578318016984801869478851843858615607891129494954595017379583319528532088055111254069874715852386305071569329096329522744304355766896648950445244523161731856403098711121722383113622298934233803081353362766142828064444866452387493035890729629049156044077239071381051585930796086670172427121883998797908792274921901699720888093776657273330010533678812202354218097512545405947522435258490771167055601360483958644670632441572215539753697817977846174064955149290862569321978468622482839722413756570560574902614079729686524145351004748216637048440319989000889524345065854122758866688116427171479924442928230863465674813919123162824586178664583591245665294765456828489128831426076900422421902267105562632111110937054421750694165896040807198403850962455444362981230987879927244284909188845801561660979191338754992005240636899125607176060588611646710940507754100225698315520005593572972571636269561882670428252483600823257530420752963450"
	maxProd, start = 0, 0
	while start < 1000-13:
		product = 1
		for i in range(13):
			product *= int(str(n)[start+i])
		if product > maxProd:
			maxProd = product
		start += 1
	return maxProd

def euler9():
	for b in range(1000):
		for a in range(b):
			c = 1000-a-b
			if a*a+b*b == c*c:
				return a*b*c

def euler10():
	return(sum(sieve(2000000)))

def euler11():
	pass

def euler12():
	pass

def euler15():
	return nCr(40, 20)

def euler16():
	total = 0
	for n in str(2**1000):
		total += int(n)
	return total

def euler19():	
	def isLeap(year):
		year = int(year)
		leap = False
		if (year % 4 == 0):
			leap = True
			if (year % 100 == 0) and (year % 400 != 0):
				leap = False
		return leap
	months = {1: 31, 2: 28, 3: 31, 4: 30, 5: 31, 6: 30, 7: 31, 8: 31, 9: 30, 10: 31, 11: 30, 12: 31}
	numberSundays = 0
	weekDay = 0
	for y in range(1900, 2001):
		for m in range(1, 13):
			daysInMonth = months[m]
			if isLeap(y) and m == 2:
				daysInMonth += 1
			for d in range(1, daysInMonth + 1):
				weekDay += 1
				if weekDay == 7:
					if d == 1 and y != 1900:
						numberSundays += 1
					weekDay = 0
	return numberSundays

def euler20():
	return sumDigits(math.factorial(100))

def euler23():
	sd=sumOfDivisors(28123)
	total=0
	for n in range(1,28123):
		valid=True
		i=1
		while n>i:
			if sd[i]>i and sd[n-i]>n-i:
				valid=False
				break
			i+=1
		if valid:total+=n
	return total

def euler24():
    return list(itertools.permutations(range(10)))[999999]

def euler25():
    x = y = count = 1
    digits = 0
    while digits < 1000:
        digits = len(str(x))
        x, y = y, x + y
        count += 1
    return count - 1

def euler26():
	cycles = 1
	number = 3
	i = 3
	while i < 1000:
		j = 1
		while j < i:
			a = 10 ** j % i
			if a == 0:break
			if a == 1:
				if j > cycles:
					cycles = j
					number = i
				break
			j += 1
		i += 2
	return number

def euler27():
	pass


def euler28():
	total = 1
	j = 2
	num = 1
	for i in range(500):
		for i in range(4):
			num += j
			total += num
		j += 2
	return total

def euler29():
	return len({a**b for a in range(2, 101) for b in range(2, 101)})

def euler30():
	m = {str(n): n**5 for n in range(10)}
	return sum(i for i in range(2, 354295) if i == sum(m[j] for j in str(i)))


def euler31():
	ways = [0]*201
	ways[0] = 1
	for x in [1,2,5,10,20,50,100,200]:
		for i in range(x, 201):
			ways[i] += ways[i-x]
	return ways[200]

def euler33():
	num, den = 1, 1
	for i in range(10, 100):
		for j in range(10, 100):
			if int(str(j)[1]) != 0 and i / j < 1:
				if str(i)[1] == str(j)[0] and int(str(i)[0]) / int(str(j)[1]) == i / j:
					num *= i
					den *= j
	return num/den*10000

def euler36():
	total = 0
	for i in range(1,1000000):
		if str(i) == str(i)[::-1] and bin(i)[2:] == bin(i)[2:][::-1]:
			total += i
	return total
	

def euler39():
	possibilities = {}
	for a in range(1, 1000):
		for b in range(1, 1000):
			c = math.sqrt(a ** 2 + b ** 2)
			if a + b + c > 1000: break
			if c.is_integer():
				possibilities.setdefault(a + b + c, 0)
				possibilities[a + b + c] += 1
	
	for k, v in possibilities.items():
		possibilities[k] /= 2
	return [k for k, v in possibilities.items() if v == max(possibilities.values())]

def euler40():
	word=''
	for i in range(1,1000000):
		word+=str(i)
	return int(word[0])*int(word[9])*int(word[99])*int(word[999])*int(word[9999])*int(word[99999])*int(word[999999])
		
def euler44():
	def generatePentagonals():
		n=1
		while True:
			yield (int)(n*(3*n-1)/2)
			n+=1
		
	pans = set()
	resset = {}
	for i in generatePentagonals():
		if i in resset:
			res = resset.get(i)
			return res[0]-res[1]
		for j in pans:
			if i-j in pans:
				resset[i+j]= (i,j)
		pans.add(i)

def euler45():
	tri, i = 40755, 286
	for i in range(286, 100000000):
		tri+=i
		if i % 2 != 0:
			if ((1 + math.sqrt(1 + (24*tri))) / 6) % 1 == 0:
				return tri
		i+=1
		
def euler46():
	for i in range(35, 1000000, 2):
		flag = False
		for j in range(int(i**0.5) + 1):
			if isPrime(i - 2 * (j ** 2)): flag = True
		if not flag: return i
		
def euler48():
	return sum(pow(x, x, 10 ** 10) for x in range(1, 1001)) % 10 ** 10

def euler53():
	c=0
	for i in range(23, 101):
		for j in range(4, i-3):
			if nCr(i, j) > 1000000: c += 1
	return c

def isLychrel(n):       #for a number < 10000
  for i in range(50):
    n = n+int(str(n)[::-1])
    if (str(n) == str(n)[::-1]):
      return False
  return True

def euler55():
	count = 0
	for n in range(10000):
		if isLychrel(n):
		  count+=1
	return count
		
def euler65():
	f =[2]
	for i in range(1, 34): f.append(1), f.append(2*i), f.append(1)
	f = f[:99][::-1]
	num, den = 1, 1
	for x in f: num, den = den, num + den * x
	return sum([int(i) for i in str(den)])

def euler112():
	pass
	
def euler114():
	seq = [1,1,0,-1,-1,0]
	n = [1,2]
	for i in range(0, 47):
		n.append(n[-1] + n[-2] + seq[i%6])
	return n[-1]

def euler115():
	f = [1] * 50 + [2]
	while True:
		f += [2 * f[-1] - f[-2] + f[-50 - 1]]
		if f[-1] > 10 ** 6: return len(f) - 1

def euler206():
	a=1389026620
	while a>(10**9):
		digits=[int(d) for d in str(a**2)]
		test, n = 0, 0
		while n<10:
			if n==0:
				if digits[-1]!=n:
					n=10
					test=1
				else: n+=1
			else:
				if digits[(2*n)-2]!=n:
					n=10
					test=1
				else: n+=1
		if test==0: return a
		else: a-=10
		
def euler349():
	return (10**18-10024) / 104 * 12 + 724 # periodic

def euler371():
	memo = {}
	def E(k,T,m, n, float_n):
		if (k,T,m) in memo:
			return memo[(k,T,m)]
		if k+m == 500: return (k+m-1)/(float_n-1)
		if T>300: return 0
		output = (k+m)/float_n*(T+1) + (k+1)/float_n*E(k,T+1,m, n, float_n)
		if m == 0: output += 1/float_n*E(k,T+1,m+1, n, float_n)
		if n-2*(k+1)>0: output += (n-2*(k+1))/float_n*E(k+1,T+1,m, n, float_n)
		memo[(k,T,m)] = output
		return output	
	return E(0,0,0, 1000, 1000)

def euler491():
	combos = itertools.combinations([0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9], 10)
	count = 0
	for c in combos:
		if (sum(c) - 45) % 11 == 0: count += 1
	answer = count * (math.factorial(10) ** 2)
	answer /= 2**10
	return 9*answer/10

def euler493():
	return 7*(1 - nCr(60, 20)/nCr(70, 20))
		
def euler500():
    P = sieve(7400050)[:500500]
    i=0
    while P[i] < (7376507)**(1/2):
        p = P[i]
        while P[i]*p < P[-1]:
            P[i] *= P[i] * p
            P.pop(-1)
        i+=1
    prod = 1
    for j in P:
        prod = (prod *j) % 500500507
    return prod