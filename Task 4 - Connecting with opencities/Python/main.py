#Main script
import sys
import geojson

#1- Collect the data.

if len(sys.argv) != 2:
    print "Usage: python main.py temperature"
    print "And you write: " + str(sys.argv)
    sys.exit(0)

#2- Read a file (logData) to check if the new value is the same as the last writed value.
#3- If the value is equal, the script will do nothing, if is different, it will write down in a new line on the file.
print "Reading the logData to check if the new values are new"
logData = open('logData', 'r')

for line in logData:
    lastLine = line

if int(sys.argv[1]) == int(lastLine):
    print "The temperature has not change since last update"
else:
    logData.close()
    logData = open('logData', 'a')
    logData.write('\n' + sys.argv[1])
    print "The new value of temperature has been added to the logData file"

#4- Create the GeoJSON.

p = geojson.FeatureCollection()
data = geojson.dumps(p)
print data


#5- Do the POST to opencities.
