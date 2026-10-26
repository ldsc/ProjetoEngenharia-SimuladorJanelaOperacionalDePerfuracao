# Comandos para Windows / VS Code

Abra o PowerShell na raiz desta pasta.

```powershell
$env:PATH = "C:\msys64\ucrt64\bin;C:\msys64\usr\bin;$env:PATH"

$build = "D:\build_parte04"

Remove-Item $build -Recurse -Force -ErrorAction SilentlyContinue

& "C:\msys64\ucrt64\bin\cmake.exe" -S . -B $build -G Ninja -DCMAKE_BUILD_TYPE=Release

& "C:\msys64\ucrt64\bin\cmake.exe" --build $build

& "$build\simulador_parte04.exe"
```

Execute o programa mantendo o terminal na raiz do projeto, pois os arquivos `data/*.csv` são lidos por caminho relativo.
