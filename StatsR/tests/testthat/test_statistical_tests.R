context("Statistical Tests")

test_that("T-test from data", {
  
  results = StatsR::t_test_summary_data(5, 9.261460, 0.2278881e-01, 195)
  
  expect_equal(2611.28380, results[["t"]])
  expect_equal(0.000e+000, results[["pval"]])
  expect_equal(194.0, results[["df"]])
  expect_equal(9.26146, results[["x1-bar"]])
  expect_equal(0.02278881, results[["sx1"]])
  expect_equal(195.0, results[["n1"]])

})

test_that("One-sample t-test", {
  
  data <- read.table(file.path(getwd(),'../../../data/weight.txt'))
  weight = data$V1
  
  results = StatsR::t_test_one_sample(25, weight)

  expect_equal(results[["t"]], -9.0783, tolerance = 1e-4)
  expect_equal(results[["pval"]], 7.9531e-06)
  expect_equal(results[["df"]], 9.0)
  expect_equal(results[["x1-bar"]], 19.25)
  expect_equal(results[["sx1"]], 2.002915, tolerance = 1e-6)
  expect_equal(results[["n1"]], 10)

})

test_that("Two-sample t-test", {
  
  us_mpg <- read.table(file.path(getwd(),'../../../data/us-mpg.txt'))
  jp_mpg <- read.table(file.path(getwd(),'../../../data/jp-mpg.txt'))

  us = us_mpg$V1
  jp = jp_mpg$V1
  
  results = StatsR::t_test_two_sample(us, jp)

  expect_equal(results[["t"]], -12.62059, tolerance=1e-5)
  expect_equal(results[["pval"]], 0.0, tolerance=1e-5)
  expect_equal(results[["df"]], 326.0)
  expect_equal(results[["x1-bar"]], 20.14458, tolerance=1e-5)
  expect_equal(results[["sx1"]], 6.41470, tolerance=1e-5)
  expect_equal(results[["n1"]], 249)
  expect_equal(results[["x2-bar"]], 30.48101, tolerance=1e-5)
  expect_equal(results[["sx2"]], 6.10771, tolerance=1e-5)
  expect_equal(results[["n2"]], 79)
  
})

test_that("Z-test from data", {
  
  results = StatsR::z_test_summary_data(5, 6.7, 7.1, 29)

  expect_equal(results[["z"]], 1.2894056580462898, tolerance=1e-5)
  expect_equal(results[["pval"]], 0.19725709541241010, tolerance=1e-5)
  expect_equal(results[["x1-bar"]], 6.7, tolerance=1e-5)
  expect_equal(results[["sx1"]], 7.1, tolerance=1e-5)
  expect_equal(results[["n1"]], 29, tolerance=1e-5)
  
})

test_that("One-sample z-test", {
  
  results = StatsR::z_test_one_sample(3, c(3, 7, 11, 0, 7, 0, 4, 5, 6, 2))
  
  expect_equal(results[["z"]], 1.3789156793307651, 1e-14)
  expect_equal(results[["pval"]], 0.16792075329459241, 1e-14)
  expect_equal(results[["x1-bar"]], 4.5, 1e-14)
  expect_equal(results[["sx1"]], 3.4399612400917157, 1e-14)
  expect_equal(results[["n1"]], 10)

})

test_that("Two-sample z-test", {
  
  x <- c( 7.8, 6.6, 6.5, 7.4, 7.3, 7.0, 6.4, 7.1, 6.7, 7.6, 6.8 )
  y <- c( 4.5, 5.4, 6.1, 6.1, 5.4, 5.0, 4.1, 5.5 )
  
  results = StatsR::z_test_two_sample(x, y)
  
  expect_equal(results[["z"]], 6.1280815146654328, 1e-14);
  expect_equal(results[["pval"]], 8.8945016827014375e-10, 1e-10);
  expect_equal(results[["x1-bar"]], 7.0181818181818167, 1e-14);
  expect_equal(results[["sx1"]], 0.46436662631627990, 1e-14);
  expect_equal(results[["n1"]], 11);
  expect_equal(results[["x2-bar"]], 5.2625000000000002, 1e-14);
  expect_equal(results[["sx2"]], 0.70698050084244091, 1e-14);
  expect_equal(results[["n2"]], 8);
  
})





















