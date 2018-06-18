Author:		Christian Carreras
File:		readme.txt
Creation Date:	10/17/2017
Due Date:	10/26/2017
Course Number:	CSC458
Course Name:	Data Mining & Predictive Analytics I
Professor:	Dr. Parson
School:		Kutztown University of Pennsylvania

Q1: 
26723 (54.3272 %)

Q2:
Month:
	< 2.5	-> '(11.3-13.54]'
	< 5.5	-> '(9.06-11.3]'
	< 9.5	-> '(6.82-9.06]'
	< 10.5	-> '(9.06-11.3]'
	>= 10.5	-> '(11.3-13.54]'
(26723/49189 instances correct)

Water oxygen levels are higher in colder months compared to warmer months.

Q3: 
This confirms the information from the readings since it shows that dissolved oxygen
levels are inversely related to water temperature. Water temperature is directly related to
the month in most regions i.e. colder in the winter, warmer in the summer and somewhere in
the middle for autumn and spring.

Q4: 
No it does not add any accuracy, it has exactly the same accuracy as OneR.
Month <= 10
|   Month <= 4
|   |   Month <= 2: '(11.3-13.54]' (79.0/30.0)
|   |   Month > 2: '(9.06-11.3]' (4361.0/2173.0)
|   Month > 4
|   |   Month <= 9
|   |   |   Month <= 6
|   |   |   |   Month <= 5: '(9.06-11.3]' (4291.0/2136.0)
|   |   |   |   Month > 5: '(6.82-9.06]' (5017.0/2297.0)
|   |   |   Month > 6: '(6.82-9.06]' (17507.0/8315.0)
|   |   Month > 9: '(9.06-11.3]' (9402.0/4326.0)
Month > 10: '(11.3-13.54]' (8532.0/3189.0)

Correctly Classified Instances: 26723 (54.3272 %)

Q5: 
19594 (39.8341 %)

Q6:
TimeOfDay:
	morning	-> '(6.82-9.06]'
	afternoon	-> '(9.06-11.3]'
	evening	-> '(6.82-9.06]'
	night	-> '(6.82-9.06]'
(19594/49189 instances correct)

Water oxygen levels are higher during the daytime and lower during nighttime.

Q7: 
This confirms the information from the readings since it shows that dissolved oxygen levels being
higher during the daytime because plants will be able to photosynthesize sunlight and create
oxygen as a by-product. This also explains the dip in dissolved oxygen at nighttime since
there will be little to no sun to allow plants to photosynthesize and create oxygen.

Q8: 
TempCelsius
Correctly Classified Instances: 29131 (59.2226 %)
TempCelsius has better accuracy than Month and TimeOfDay.
This is the best predictor of OxygenMgPerLiter so far.

Q9:
TempCelsius:
	< 1.05	-> '(11.3-13.54]'
	< 1.85	-> '(13.54-15.78]'
	< 1.95	-> '(11.3-13.54]'
	< 2.05	-> '(13.54-15.78]'
	< 2.1500000000000004	-> '(11.3-13.54]'
	< 2.25	-> '(13.54-15.78]'
	< 7.45	-> '(11.3-13.54]'
	< 7.55	-> '(9.06-11.3]'
	< 8.149999999999999	-> '(11.3-13.54]'
	< 8.25	-> '(9.06-11.3]'
	< 8.350000000000001	-> '(11.3-13.54]'
	< 15.05	-> '(9.06-11.3]'
	< 15.25	-> '(6.82-9.06]'
	< 16.05	-> '(9.06-11.3]'
	< 16.45	-> '(6.82-9.06]'
	< 16.75	-> '(9.06-11.3]'
	< 26.85	-> '(6.82-9.06]'
	< 27.05	-> '(4.58-6.82]'
	< 27.25	-> '(6.82-9.06]'
	< 27.35	-> '(4.58-6.82]'
	< 27.85	-> '(6.82-9.06]'
	< 28.65	-> '(4.58-6.82]'
	< 29.15	-> '(6.82-9.06]'
	< 29.25	-> '(4.58-6.82]'
	< 29.65	-> '(6.82-9.06]'
	< 29.75	-> '(9.06-11.3]'
	< 29.85	-> '(6.82-9.06]'
	< 30.05	-> '(9.06-11.3]'
	< 31.55	-> '(6.82-9.06]'
	< 32.05	-> '(4.58-6.82]'
	< 33.349999999999994	-> '(15.78-18.02]'
	>= 33.349999999999994	-> '(13.54-15.78]'
	?	-> '(9.06-11.3]'

The general pattern is the higher the temperature of the water, the lower amount of dissolved oxygen.

Q10:
HourOfYear
Correctly Classified Instances: 27910 (56.7403 %)
HourOfYear has better accuracy than Month and TimeOfDay but not TempCelsius.
TempCelsius is still the best predictor of OxygenMgPerLiter.

Q11:
HourOfYear:
	< 1332.0	-> '(13.54-15.78]'
	< 1380.0	-> '(11.3-13.54]'
	< 1404.0	-> '(13.54-15.78]'
	< 1572.0	-> '(11.3-13.54]'
	< 1596.0	-> '(13.54-15.78]'
	< 1836.0	-> '(11.3-13.54]'
	< 2148.0	-> '(9.06-11.3]'
	< 2172.0	-> '(11.3-13.54]'
	< 2340.0	-> '(9.06-11.3]'
	< 2364.0	-> '(11.3-13.54]'
	< 2436.0	-> '(9.06-11.3]'
	< 2508.0	-> '(11.3-13.54]'
	< 2748.0	-> '(9.06-11.3]'
	< 2772.0	-> '(11.3-13.54]'
	< 2868.0	-> '(9.06-11.3]'
	< 2892.0	-> '(11.3-13.54]'
	< 3060.0	-> '(9.06-11.3]'
	< 3084.0	-> '(6.82-9.06]'
	< 3372.0	-> '(9.06-11.3]'
	< 3420.0	-> '(6.82-9.06]'
	< 3492.0	-> '(9.06-11.3]'
	< 3732.0	-> '(6.82-9.06]'
	< 3852.0	-> '(9.06-11.3]'
	< 3876.0	-> '(6.82-9.06]'
	< 3900.0	-> '(9.06-11.3]'
	< 6444.0	-> '(6.82-9.06]'
	< 6468.0	-> '(9.06-11.3]'
	< 6540.0	-> '(6.82-9.06]'
	< 6636.0	-> '(9.06-11.3]'
	< 6780.0	-> '(6.82-9.06]'
	< 7404.0	-> '(9.06-11.3]'
	< 8724.0	-> '(11.3-13.54]'
	>= 8724.0	-> '(13.54-15.78]'

The general pattern is that the colder the time of year in which the hour exits, the higher
the amount of dissolved oxygen is. The warmer the time of year, the lower the amount of DO is.

Q12:
OneR
Correctly Classified Instances: 29131 (59.2226 %)

J48
Correctly Classified Instances: 40340 (82.0102 %)

Random Tree
Correctly Classified Instances: 40286 (81.9004 %)

J48 is the most predictive.

Q13:
OneR's rule is by far the easiest to understand in terms of looking because it maps a single
value of the used predictive variable right to the OxygenMgPerLiter value.
