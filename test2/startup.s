/* startup.s - 最簡化的啟動檔 */

.syntax unified
.thumb

.global _start
_start:
    bl main       // 呼叫 main()
    b .           // 進入無窮迴圈，避免返回到不存在的 OS
