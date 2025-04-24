# [Gold II] 문자열 자르기 - 13260 

[문제 링크](https://www.acmicpc.net/problem/13260) 

### 성능 요약

메모리: 13988 KB, 시간: 16 ms

### 분류

다이나믹 프로그래밍

### 제출 일자

2025년 4월 24일 21:51:07

### 문제 설명

<p>길이가 N인 문자열을 두 조각으로 자르는데 필요한 비용은 N이다.</p>

<p>문자열을 잘라야 하는 위치가 주어졌을 때, 문자열을 자르는 비용의 최솟값을 구하는 프로그램을 작성하시오.</p>

<p>예를 들어, 3, 8, 10번 (첫 문자: 1)의 다음 위치에서 문자열을 잘라야 하는 경우를 생각해보자. 즉, 문자열이 <code>thisisastringofchars</code>인 경우에, 3, 8, 10번 문자의 다음 위치를 <span style="font-family:monospace">|</span>로 표시해보면 <code>thi|sisas|tr|ingofchars</code> 이다.</p>

<p>이때, 가장 왼쪽에서부터 차례대로 자르면 필요한 비용은 49이다.</p>

<pre>thisisastringofchars     (문자열)
thi sisastringofchars    (비용: 20)
thi sisas tringofchars   (비용: 17)
thi sisas tr ingofchars  (비용: 12)
                         총: 49.</pre>

<p>가장 오른쪽부터 문자열을 자르면 필요한 비용은 38이다.</p>

<pre>thisisastringofchars     (문자열)
thisisastr ingofchars    (비용: 20)
thisisas tr ingofchars   (비용: 10)
thi sisas tr ingofchars  (비용: 8)
                         총: 38.</pre>

<p>문자열이 주어졌을 때, 입력으로 주어진 위치에서 문자열을 자르는 비용의 최솟값을 구하는 프로그램을 작성하시오. 문자열을 자르는 순서는 상관없다.</p>

### 입력 

 <p>첫째 줄에 문자열의 길이 N (2 ≤ N ≤ 10,000,000)과 잘라야 하는 위치의 수 M (1 ≤ M ≤ 1000, M < N)이 주어진다.</p>

<p>둘째 줄에는 문자열을 잘라야 하는 위치가 주어진다.</p>

### 출력 

 <p>문자열을 입력으로 주어진대로 자르기 위해 필요한 비용의 최솟값을 출력한다.</p>

