import os
import subprocess

from . import utils


def generate_cmake():
    res = subprocess.run([
        "cmake",
        ".",
        "-G",
        "Ninja",
        "--preset",
        "conan-debug",
        "-D",
        "SLANGC_EXECUTABLE=" + utils.get_slangc()
    ])

    if res.returncode != 0:
        raise RuntimeError("Failed to generate cmake")


def build():
    print("================ BUILDING ===============", flush=True)
    res = subprocess.run([
        "ninja",
        "-C",
        os.path.join(
            "build",
            "Debug",
        ),
    ])

    if res.returncode != 0:
        raise RuntimeError("Build failed")
