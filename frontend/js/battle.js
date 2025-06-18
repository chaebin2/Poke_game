/* global switchBackground */

document.addEventListener("DOMContentLoaded", () => {
  const btn = document.querySelector("#battle-section button");
  if (btn) btn.onclick = startBattle;
});

async function startBattle() {
  switchBackground("battle");
  const logBox = document.getElementById("battle-log");
  logBox.innerText = "전투 중...";
  try {
    const res = await fetch("http://localhost:8000/battle");
    const data = await res.json();
    renderBattleLog(data);
  } catch (err) {
    console.error("[battle] /battle 실패", err);
    logBox.innerText = "전투 진행 중 오류 발생!";
  }
}

function renderBattleLog(data) {
  const logBox = document.getElementById("battle-log");
  if (data.output) {
    // C 백엔드가 문자열 로그를 넘겨주는 형태
    logBox.innerText = data.output;
  } else {
    logBox.innerText = JSON.stringify(data, null, 2);
  }
}
