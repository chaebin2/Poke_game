/* global switchBackground */

document.addEventListener("DOMContentLoaded", () => {
  const btn = document.querySelector("#battle-section button");
  if (btn) btn.onclick = startBattle;
});

async function startBattle() {
  switchBackground("battle");
  const logBox = document.getElementById("battle-log");
  logBox.innerText = "���� ��...";
  try {
    const res = await fetch("http://localhost:8000/battle");
    const data = await res.json();
    renderBattleLog(data);
  } catch (err) {
    console.error("[battle] /battle ����", err);
    logBox.innerText = "���� ���� �� ���� �߻�!";
  }
}

function renderBattleLog(data) {
  const logBox = document.getElementById("battle-log");
  if (data.output) {
    // C �鿣�尡 ���ڿ� �α׸� �Ѱ��ִ� ����
    logBox.innerText = data.output;
  } else {
    logBox.innerText = JSON.stringify(data, null, 2);
  }
}
