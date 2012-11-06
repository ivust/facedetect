setwd('/home/ivust/facedetect/output')
smile <- read.csv("smile.csv", header = FALSE)
not_smile <- read.csv("not_smile.csv", header = FALSE)




res_s <- data.frame(num=1:200)
res_ns <- data.frame(num=1:200)
res_s$num <- NULL
res_ns$num <- NULL
write.table(res_s, "test.csv", sep = ",")

for(i in 2:7) {
  for(j in 1:(i-1)){
    cat(j)
    cat("\n")
    tmp_s <- sqrt((smile[,i*2 + 2] - smile[,j*2 + 2])^2 + (smile[,i*2 + 2 + 1] - smile[,j*2 + 2 + 1])^2)
    tmp_ns <- sqrt((not_smile[,i*2 + 2] - not_smile[,j*2 + 2])^2 + (not_smile[,i*2 + 2 + 1] - not_smile[,j*2 + 2 + 1])^2)
    res_s[paste0("dist_",j,"_",i)] <- tmp_s
    res_ns[paste0("dist_",j,"_",i)] <- tmp_ns
  }
}

