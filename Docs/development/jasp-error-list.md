
List of Error Messages
======================

Rationale
---------

The intention of this page is to list all the error messages that can be produced by JASP. The motivation for this is so that developers can see what error messages are used elsewhere in JASP, and use the same if appropriate, or create similar messages. Consistent error messages are important because it allows the user to generalise their understanding and problem solving from similar but different contexts. Coherent error messages also lead people to perceive JASP as a 'professional', polished and dependable product.

When adding new error messages to JASP, developers should refer to this document, and see if an appropriate error message isn't already used elsewhere. If an appropriate one does not exist, then new messages should be created with a similar flavour to what is listed here. New error messages should then be added to this document, and will undergo peer-review with the pull request.

Error messages are generally of one of two forms; An *analysis error*, or a *value error*.

An analysis error generally refers to either a whole results table, or all the results tables in an analysis. In this case, the table is displayed in grey, and the error message is displayed prominently over the top. This is intended for situations where as a result of the error there are no meaningful results that can be reported. For example, an ANOVA where an independent variable has only one level; there is no meaningful F-statistic, degrees of freedom or p-value.

In contrast, a *value error* is where the error pertains to one or few terms. For example, a t-test analysis may perform many t-tests, but only one of these t-tests may produce an error. All the other values in the table are correct and legitimate. In this case, we place an NaN in the affected cell in the table, and place a footnote which contains the error message. It is also possible to provide warnings, and useful information in this way as well (for example, that a levene's test on t-test data is significant)

Error Messages
--------------

### T-Tests

#### Independent Samples

overall errors

- The Grouping Variable must have 2 levels

value errors for *t*

- t-statistic is undefined -- the dependent variable contains infinity
- t-statistic is undefined -- the grouping variable contains less than two levels once missing values in the dependent are excluded
- t-statistic is undefined -- one or both levels of the dependent contains all the same value (the variance is zero)
- t-statistic is undefined -- one or both levels of the dependent contain too few observations
- *Note.* All tests, variances of groups assumed equal
- *Note.* All tests, variances of groups not assumed equal
- *Note.* All tests, hypothesis is group *X* greater than group *Y*
- *Note.* All tests, hypothesis is group *X* less than group *Y*
- Levene's test is significant (p < .05), suggesting a violation of the equal variance assumption

#### Bayesian Independent Samples T-Test

overall errors

- The Grouping Variable must have 2 levels

value errors for *BF*

* BayesFactor is undefined -- the dependent variable contains infinity
* BayesFactor is undefined -- the grouping variable contains less than two levels once missing values in the dependent are excluded
* BayesFactor is undefined -- one or both levels of the dependent contain all the same value (the variance is zero)
* BayesFactor is undefined -- one or both levels of the dependent contain too few observations
* *Note.* All tests, hypothesis is group *$X* greater than group *Y*
* *Note.* All tests, hypothesis is group *$X* less than group *Y*

#### One Sample T-Test

value errors for *t*

* t-statistic is undefined -- the sample contains infinity
* t-statistic is undefined -- the sample contains all the same value (the variance is zero)
* t-statistic is undefined -- sample contains only one value
* *Note.* All tests, hypothesis is sample mean is greater than *X*
* *Note.* All tests, hypothesis is sample mean is less than *X*
* *Note.* All tests, hypothesis is sample mean is different to *X*

#### Bayesian One Sample T-Test

value error for *BF*

- BayesFactor is undefined -- the sample contains infinity
- BayesFactor is undefined -- the sample has too few observations

#### Paired Sample T-Test

value errors for *t*

* t-statistic is undefined -- one or both of the variables contain infinity
* t-statistic is undefined -- one or both of the variables contain all the same value (the variance is zero)
* t-statistic is undefined -- one or both of the variables contain only one value
* *Note.* All tests, hypothesis is group one greater than group two
* *Note.* All tests, hypothesis is group one less than group two

#### Bayesian Paired Sample T-Test

value errors for *BF*

* BayesFactor is undefined -- one or both of the variables contain infinity
* BayesFactor is undefined -- one or both of the variables has too few observations (possibly only after missing values are excluded)

#### ANOVA

* Factor(s): *X, Y, Z* contain(s) less than two levels. (Possibly only after rows with missing values are excluded)