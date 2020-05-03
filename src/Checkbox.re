[@react.component]
let make = (~checked=false, ~onChange, ~style=?) => {
  <div
    className=TW.([Display(InlineFlex)]->make)
    onClick={_ => onChange(!checked)}
    tabIndex=0
    ?style>
    {checked
       ? <Icons.CheckCircle color="#90cdf4" />
       : <Icons.Circle color="#90cdf4" />}
  </div>;
};