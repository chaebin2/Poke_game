import subprocess

result = subprocess.run(
    ["C:/Users/cheab/source/repos/Poke_game/build/bin/Debug/poke_game.exe", "shop"],
    capture_output=True,
    text=True,
    timeout=5
)

print("✅ STDOUT:")
print(result.stdout)

print("❌ STDERR:")
print(result.stderr)