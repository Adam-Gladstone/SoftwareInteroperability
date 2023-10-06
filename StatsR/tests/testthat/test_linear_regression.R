context("Linear Regression")

test_that("Linear Regression Values", {
  
  x <- 1:20                                        # Make x = (1, 2, . . . , 20).
  w <- 1 + sqrt(x)/2                               # A ‘weight’ vector of standard deviations.
  y = x + rnorm(x)*w

  dummy <- data.frame(x = x, y = y)                # Make a data frame of two columns, x and y
  fm <- lm(y ~ x, data=dummy)                      # Fit a simple linear regression

  r = cor(dummy)
  r2 = cor(dummy)^2

  results = StatsR::linear_regression(x, y)

  expect_equal(fm$coefficients[["(Intercept)"]], results[["b0"]])
  expect_equal(fm$coefficients[["x"]], results[["b1"]])
  expect_equal(r[2,1], results[["r"]])
  expect_equal(r2[2,1], results[["r2"]])
})