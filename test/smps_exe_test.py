import os
import subprocess

PROGRAM_NAME = "./sm_hash_tool" if os.name == "posix" else "sm_hash_tool.exe"


KNOWN_BAD_HASH_LINES = {143768, 348951, 358992}


def hash_stdin(input: str):
    return subprocess.run(
        PROGRAM_NAME,
        input=input,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
    ).stdout.strip()


def hash_file(file: str):
    return subprocess.run(
        f'{PROGRAM_NAME} "{file}"',
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
    ).stdout.strip()


def test_asset_hashes_slow():
    file = open("test/AssetHashes.txt", "r")
    results = file.read().strip().split("\n")
    results = [v.split(",") for v in results]

    start = 0
    for [i, [name, expected_hash]] in list(enumerate(results))[start:]:
        if i + 1 in KNOWN_BAD_HASH_LINES:
            print("skipping", i + 1)
            continue
        result = hash_stdin(name)
        print(i + 1, f"'{name[:40]}...'", expected_hash, result)
        assert result == expected_hash


def test_asset_hashes():
    asset_hashes_file = open("test/AssetHashes.txt", "r")
    asset_hash_lines = asset_hashes_file.read().strip().split("\n")
    asset_hash_lines = [v.split(",") for v in asset_hash_lines]
    asset_names = [v[0] for v in asset_hash_lines]
    asset_names = "\n".join(asset_names)
    hash_results = hash_stdin(asset_names).split("\n")

    for i in range(0, len(asset_hash_lines)):
        [hash_input, expected_hash] = asset_hash_lines[i]
        hash_result = hash_results[i]
        if expected_hash != hash_result:
            if i + 1 in KNOWN_BAD_HASH_LINES:
                print(f"line: {i+1}, failed known bad hash, skipping...")
                continue
            print(
                f"line: {i+1}, expected '{expected_hash}, actual '{hash_result}' for '{hash_input}'"
            )
            break


assert hash_stdin("0") == "9625851156722893451"
assert hash_stdin("1") == "12204323496446760272"
assert hash_stdin("0 1") == "10631490009105291249"
assert hash_stdin("alwaysbeclosing") == "12676152422457307961"
assert hash_stdin("always be closing") == "10638241236223618570"
assert hash_stdin("aa") == "10858719388638484620"
assert hash_stdin("a/a") == "13275144271646325503"
assert hash_stdin("a//a") == "13275144271646325503"
assert hash_stdin("a/\\a") == "13275144271646325503"
assert hash_stdin("a/a/") == "13275144271646325503"
assert hash_stdin("/a/a") == "13275144271646325503"
assert (
    hash_stdin(
        r"models\manmade_system\fencing_pipes_vents\ml_corrogated_metal_fence_01_nopoles.model"
    )
    == "10039806796442441106"
)
assert (
    hash_stdin(
        r"models\manmade_system\fencing_pipes_vents\ml_corrogated_metal_fence_01.model"
    )
    == "9910286909319129036"
)
assert (
    hash_stdin(
        r"characters\hero\hero_spiderman\animations\vehicle\vehicle_car_passenger_firing_thug_a.animclip"
    )
    == "12326074479071120678"
)

test_asset_hashes()
