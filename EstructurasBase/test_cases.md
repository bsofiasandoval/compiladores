# Casos de Prueba - Tarea 1

## Stack<int>

| Descripción | Resultado Esperado | Resultado Obtenido |
|---|---|---|
| isEmpty() en stack vacío | true | true |
| push(1), push(2), push(3) → size() | 3 | 3 |
| push(1), push(2), push(3) → getTop() | 3 | 3 |
| pop() → getTop() | 2 | 2 |
| pop() hasta vaciar → isEmpty() | true | true |
| pop() en stack vacío | lanza out_of_range | lanza out_of_range |

## Queue<string>

| Descripción | Resultado Esperado | Resultado Obtenido |
|---|---|---|
| isEmpty() en queue vacío | true | true |
| push("first"), push("second"), push("third") → size() | 3 | 3 |
| getFront() | "first" | "first" |
| getBack() | "third" | "third" |
| pop() → getFront() | "second" | "second" |
| pop() hasta vaciar → isEmpty() | true | true |
| pop() en queue vacío | lanza out_of_range | lanza out_of_range |

## Table<string, int>

| Descripción | Resultado Esperado | Resultado Obtenido |
|---|---|---|
| isEmpty() en tabla vacía | true | true |
| insert("age",21), insert("year",2026), insert("schoolYear",4) → size() | 3 | 3 |
| get("age") | 21 | 21 |
| insert("age", 25) → get("age") | 25 | 25 |
| contains("age") | true | true |
| contains("name") | false | false |
| remove("age") → contains("age") | false | false |
| remove("age") → size() | 2 | 2 |
| get() en llave inexistente | lanza out_of_range | lanza out_of_range |
| remove() en llave inexistente | lanza out_of_range | lanza out_of_range |