# [CII Best Practices Badge Program](https://bestpractices.coreinfrastructure.org/en)

The [Linux Foundation (LF)](https://www.linuxfoundation.org/) [Core Infrastructure Initiative (CII)](https://www.coreinfrastructure.org/) Best Practices badge is a way for Free/Libre and Open Source Software (FLOSS) projects to show that they follow best practices. 

## [FLOSS Best Practices Criteria (Passing Badge)](https://bestpractices.coreinfrastructure.org/en/criteria/0)

> NOTE: 
>
> 1、通过tool来发现bug



### Basics

> NOTE: 
>
> 1、主要针对的是FLOSS

### Change Control

> NOTE: 
>
> 1、其实就是版本控制

#### Public version-controlled source repository

#### Unique version numbering

#### Release notes



### Quality

#### Working build system

> NOTE: 
>
> 1、一般和CI放到一起



#### Automated test suite

> NOTE: 
>
> 1、自动化测试



[[test](https://bestpractices.coreinfrastructure.org/en/criteria/0#0.test)]

> NOTE: 
>
> 1、一般都是使用的开源单元测试 框架

The project MUST use at least one automated test suite that is publicly released as FLOSS (this test suite may be maintained as a separate FLOSS project). The project MUST clearly show or document how to run the test suite(s) (e.g., via a continuous integration (CI) script or via documentation in files such as BUILD.md, README.md, or CONTRIBUTING.md). [[test](https://bestpractices.coreinfrastructure.org/en/criteria/0#0.test)]

[[test_most](https://bestpractices.coreinfrastructure.org/en/criteria/0#0.test_most)]

It is SUGGESTED that the test suite cover most (or ideally all) the code branches, input fields, and functionality. [[test_most](https://bestpractices.coreinfrastructure.org/en/criteria/0#0.test_most)]

[[test_continuous_integration](https://bestpractices.coreinfrastructure.org/en/criteria/0#0.test_continuous_integration)]

> NOTE: 
>
> 1、这是否就是冒烟测试

It is SUGGESTED that the project implement continuous integration (where new or changed code is frequently integrated into a central code repository and automated tests are run on the result). [[test_continuous_integration](https://bestpractices.coreinfrastructure.org/en/criteria/0#0.test_continuous_integration)]



### Analysis

#### Static code analysis

#### Dynamic code analysis

[[dynamic_analysis](https://bestpractices.coreinfrastructure.org/en/criteria/0#0.dynamic_analysis)]

> NOTE: 
>
> 1、对于C、C++类语言，这是必须的

It is SUGGESTED that at least one dynamic analysis tool be applied to any proposed major production release of the software before its release. [[dynamic_analysis](https://bestpractices.coreinfrastructure.org/en/criteria/0#0.dynamic_analysis)]



[[dynamic_analysis_enable_assertions](https://bestpractices.coreinfrastructure.org/en/criteria/0#0.dynamic_analysis_enable_assertions)]

It is SUGGESTED that the project use a configuration for at least some dynamic analysis (such as testing or fuzzing) which enables many assertions. In many cases these assertions should *not* be enabled in production builds. [[dynamic_analysis_enable_assertions](https://bestpractices.coreinfrastructure.org/en/criteria/0#0.dynamic_analysis_enable_assertions)]