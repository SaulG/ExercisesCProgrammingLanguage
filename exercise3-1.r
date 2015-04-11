data = read.csv("exercise3-1.dat", sep=" ", header=FALSE)
#data
names(data) = c("version", "tiempo", "unidad", "mugre")
#data$version
#data$tiempo
#v1 = data[data$version == "V1", ]
#v2 = data[data$version == "V2", ]
#summary(v1)
#summary(v2)
v1 = data[data$version == "V1", ]$tiempo
v2 = data[data$version == "V2", ]$tiempo
#summary(v1)
#summary(v2)
png("box.png")
boxplot(v1, v2, names=c("Orig", "Mod"))
graphics.off()