async function fetchShopPokemon() {
  try {
    const res = await fetch("http://127.0.0.1:8000/shop");  // FastAPI���� �����ؾ� �ϴ� API
    const data = await res.json();

    if (!data.shop) return;

    const container = document.getElementById("pokemon-list");
    data.shop.forEach(pokemon => {
      const card = document.createElement("div");
      card.className = "pokemon-card";

      card.innerHTML = `
        <img src="${pokemon.image_url}" alt="${pokemon.name}" />
        <h3>${pokemon.name}</h3>
        <p>HP: ${pokemon.hp}</p>
        <p>ATK: ${pokemon.attack}</p>
        <p>DEF: ${pokemon.defense}</p>
        <p>SPD: ${pokemon.speed}</p>
        <p>����: ${pokemon.price} ����Ʈ</p>
        <button onclick="buyPokemon(${pokemon.id})">����</button>
      `;

      container.appendChild(card);
    });
  } catch (err) {
    console.error("���� ������ �ҷ����� ����:", err);
  }
}

async function buyPokemon(pokemonId) {
  const res = await fetch("http://127.0.0.1:8000/buy", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ pokemon_id: pokemonId }),
  });

  const result = await res.json();
  alert(result.message || "���� ó�� �Ϸ�");
}

window.onload = fetchShopPokemon;
async function fetchShopPokemon() {
  try {
    const res = await fetch("http://127.0.0.1:8000/shop");  // FastAPI���� �����ؾ� �ϴ� API
    const data = await res.json();

    if (!data.shop) return;

    const container = document.getElementById("pokemon-list");
    data.shop.forEach(pokemon => {
      const card = document.createElement("div");
      card.className = "pokemon-card";

      card.innerHTML = `
        <img src="${pokemon.image_url}" alt="${pokemon.name}" />
        <h3>${pokemon.name}</h3>
        <p>HP: ${pokemon.hp}</p>
        <p>ATK: ${pokemon.attack}</p>
        <p>DEF: ${pokemon.defense}</p>
        <p>SPD: ${pokemon.speed}</p>
        <p>����: ${pokemon.price} ����Ʈ</p>
        <button onclick="buyPokemon(${pokemon.id})">����</button>
      `;

      container.appendChild(card);
    });
  } catch (err) {
    console.error("���� ������ �ҷ����� ����:", err);
  }
}

async function buyPokemon(pokemonId) {
  const res = await fetch("http://127.0.0.1:8000/buy", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ pokemon_id: pokemonId }),
  });

  const result = await res.json();
  alert(result.message || "���� ó�� �Ϸ�");
}

window.onload = fetchShopPokemon;
