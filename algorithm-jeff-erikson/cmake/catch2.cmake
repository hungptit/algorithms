include(FetchContent)

FetchContent_Declare(
  catch2
  GIT_REPOSITORY git@github.com:catchorg/Catch2.git
  GIT_TAG v3.6.0
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(catch2)
