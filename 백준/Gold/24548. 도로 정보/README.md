# [Gold III] 도로 정보 - 24548 

[문제 링크](https://www.acmicpc.net/problem/24548) 

### 성능 요약

메모리: 2020 KB, 시간: 0 ms

### 분류

누적 합

### 제출 일자

2025년 9월 12일 00:10:39

### 문제 설명

<p>현대오토에버는 국내 최초로 차량 운전 지원용 지도 생성을 위한 MMS (Mobile Mapping System) 기반 정밀지도 구축 시스템을 도입했다. 이는 고성능 레이저 스캐너 장치인 라이다 (LiDAR) 를 포함한 다양한 센서를 활용하여, 도로 및 주변 지형 등의 정보를 빠짐없이 취득하는 최첨단 3차원 공간정보 조사 시스템이다. 이 지도 정보를 활용하면 운전자에게 여러 편의 기능을 제공해줄 수 있다. 예를 들어 운전자에게 고성능 내비게이션 서비스를 제공할 수도 있고, 더 나아가 자율 주행에 필요한 도로 교통 정보를 제공해 줄 수도 있게 된다.</p>

<p>현대오토에버의 연구원 알정이는 오늘 정밀지도 정보 수집 차량으로부터 특정 시내의 도로를 촬영한 데이터를 전달받았다. 이 데이터에는 도로 주변의 나무, 잔디, 울타리 그리고 사람들을 촬영한 내용이 담겨 있다. 알정이는 이를 내비게이션 시스템에 사용할 수 있는 데이터로 가공할 것이다. 본격적인 작업에 앞서 알정이는 전달받은 데이터의 특성을 파악해보려고 한다.</p>

<p>도로 데이터를 전부 보고 있을 시간은 없으므로 알정이는 도로의 <strong>흥미로운 구간</strong> 하나를 뽑아서 보려고 한다. 도로는 나무를 나타내는 <code>T</code>, 잔디를 나타내는 <code>G</code>, 울타리를 나타내는 <code>F</code> 혹은 사람을 나타내는 <code>P</code> 로 이루어진 길이 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D441 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>N</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$N$</span></mjx-container>의 문자열로 표현된다. 도로 구간이란 도로의 연속된 일부분을 의미하며, 도로의 연속 부분 문자열로 표현된다. <strong>흥미로운 구간</strong>이란, 길이가 1 이상인 도로 구간 중 그에 속한 모든 물체의 수가 3의 배수인 것을 의미한다. 예를 들어 도로 구간에 나무 3개, 울타리 3개가 담겼다면 그 도로 구간은 <strong>흥미로운 구간</strong>이지만, 나무 3개와 울타리 2개가 담겼다면 이는 <strong>흥미로운 구간</strong>이 아니다.</p>

<p>도로의 정보가 주어졌을 때, <strong>흥미로운 구간</strong>이 될 수 있는 도로 구간의 개수를 구해보자.</p>

### 입력 

 <p>첫 번째 줄에 정수 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D441 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>N</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$N$</span></mjx-container>이 주어진다. (<mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mn class="mjx-n"><mjx-c class="mjx-c31"></mjx-c></mjx-mn><mjx-mo class="mjx-n" space="4"><mjx-c class="mjx-c2264"></mjx-c></mjx-mo><mjx-mi class="mjx-i" space="4"><mjx-c class="mjx-c1D441 TEX-I"></mjx-c></mjx-mi><mjx-mo class="mjx-n" space="4"><mjx-c class="mjx-c2264"></mjx-c></mjx-mo><mjx-mn class="mjx-n" space="4"><mjx-c class="mjx-c31"></mjx-c><mjx-c class="mjx-c30"></mjx-c><mjx-c class="mjx-c30"></mjx-c></mjx-mn><mjx-mstyle><mjx-mspace style="width: 0.167em;"></mjx-mspace></mjx-mstyle><mjx-mn class="mjx-n"><mjx-c class="mjx-c30"></mjx-c><mjx-c class="mjx-c30"></mjx-c><mjx-c class="mjx-c30"></mjx-c></mjx-mn></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mn>1</mn><mo>≤</mo><mi>N</mi><mo>≤</mo><mn>100</mn><mstyle scriptlevel="0"><mspace width="0.167em"></mspace></mstyle><mn>000</mn></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$1 \leq N \leq 100\,000$</span></mjx-container> )</p>

<p>두 번째 줄에 도로를 표현한 길이 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D441 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>N</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$N$</span></mjx-container>의 문자열이 주어진다.</p>

### 출력 

 <p>첫 번째 줄에 <strong>흥미로운 구간</strong>의 개수를 출력한다.</p>

