# Statistical T-tests

#
# t-tests
#

# No sample data
StatsR::t_test_summary_data(5, 9.261460, 0.2278881e-01, 195)

# Interactive version
# data <- read.table(file.choose())

#
# One-sample t-test
#
data <- read.table("../data/weight.txt")
weight = data$V1

t.test(weight, mu = 25)

StatsR::t_test_one_sample(25, weight)

#
# Two-sample t-test
#
us_mpg <- read.table("../data/us-mpg.txt")
jp_mpg <- read.table("../data/jp-mpg.txt")

us = us_mpg$V1
jp = jp_mpg$V1

StatsR::t_test_two_sample(us, jp)

#
# z-tests
#

# No sample data
StatsR::z_test_summary_data(5, 6.7, 7.1, 29)

# One-sample data
StatsR::z_test_one_sample(3, c(3, 7, 11, 0, 7, 0, 4, 5, 6, 2))

# Two-sample data
x <- c( 7.8, 6.6, 6.5, 7.4, 7.3, 7.0, 6.4, 7.1, 6.7, 7.6, 6.8 )
y <- c( 4.5, 5.4, 6.1, 6.1, 5.4, 5.0, 4.1, 5.5 )

StatsR::z_test_two_sample(x, y)

#
# t-test using a class
#

library(Rcpp)
require(Rcpp)
library(formattable)

moduleStatsTests <- Module("StatsTests", PACKAGE="StatsR")
ttest0 <- new(moduleStatsTests$TTest, 5, 9.261460, 0.2278881e-01, 195)
if(ttest0$Perform()) {
  results <- ttest0$Results()
  print(results)
  results <- as.data.frame(results)
  formattable(results)
  
} else {
  print("T-test from summary data failed.")
}

ttest1 <- new(moduleStatsTests$TTest, 25, weight)
if(ttest1$Perform()) {
  print(ttest1$Results())
} else {
  print("One-sample t-test failed.")
}

cols <- list('x1'=us, 'x2'=jp)

ttest2 <- new(moduleStatsTests$TTest, cols)
if(ttest2$Perform()) {
  print(ttest2$Results())
} else {
  print("Two-sample t-test failed.")
}


#
# z-test using a class
#

library(Rcpp)
library(formattable)

moduleStatsTests <- Module("StatsTests", PACKAGE="StatsR")
ztest0 <- new(moduleStatsTests$ZTest, 5, 6.7, 7.1, 29)
if(ztest0$Perform()) {
  results <- ztest0$Results()
  print(results)
  results <- as.data.frame(results)
  formattable(results)
  
} else {
  print("Z-test from summary data failed.")
}

ztest1 <- new(moduleStatsTests$ZTest, 3, c(3, 7, 11, 0, 7, 0, 4, 5, 6, 2))
if(ztest1$Perform()) {
  print(ztest1$Results())
} else {
  print("One-sample z-test failed.")
}

cols <- list('x1'=x, 'x2'=y)

ztest2 <- new(moduleStatsTests$ZTest, cols)
if(ztest2$Perform()) {
  print(ztest2$Results())
} else {
  print("Two-sample z-test failed.")
}

