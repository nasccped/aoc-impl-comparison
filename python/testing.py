import io
import sys
from contextlib import redirect_stdout

"""Testing utilities (similar to rust testing (form cargo))"""

def run_test(func, mod_name: str = "undefined"):
    """
    Receives a func argument that return bool and don't receive
    arguments. All the content printed in that function will be
    redirected to this function to be printed latter.

    The second argument of this func is the module name (advent day).
    If not specified, \"undefined\" will be set.
    """
    print(
        f"Running {mod_name}::{func.__name__}",
        end=" "
    )
    buffer = io.StringIO()
    with redirect_stdout(buffer):
        result = func()
    if result:
        print("\033[92mok\033[0m")
    else:
        print("\033[91mfail\033[0m")
        print(buffer.getvalue())

def assert_eq(value_1,
              value_2,
              message: str | None = None) -> bool:
    """
    Assert if two values are equals.
    Probably won't work for non-primitive-like types (ie classes).

    Return true if assert success, else, false.
    """

    if value_1 != value_2:
        print(
            message \
            if message \
            else f"Assert Panic: left value is `{value_1}` but right value is `{value_2}`"
            )
        return False
    return True
