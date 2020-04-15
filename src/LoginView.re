open TW;
open Belt;
open ReasonUrql.Hooks;

[@react.component]
let make = () => {
  let (email, setLogin) = React.useState(() => "");
  let (password, setPassword) = React.useState(() => "");

  let ({fetching, data, error}, signIn) = LoginQuery.use(~email, ~password);
  let {setToken}: AuthContext.t = Auth.use();

  React.useEffect1(
    () => {
      let token = data->Option.map(data => data##login##token);
      if (Option.isSome(token)) {
        setToken(token);
      };
      None;
    },
    [|data|],
  );

  <div className={[Display(Flex), MinHeight(MinHScreen)]->make}>
    <div
      className={
        [
          Display(Flex),
          FlexDirection(FlexCol),
          AlignItems(ItemsCenter),
          Width(W6_12),
          Margin(MxAuto),
          JustifyContent(JustifyCenter),
        ]
        ->make
      }>
      <Text className=[Margin(My4)]> {j|Login|j} </Text>
      <Input
        value=email
        onChange={value => setLogin(_ => value)}
        placeholder={j|Login|j}
        className=[Margin(My4)]
      />
      <Input
        value=password
        onChange={value => setPassword(_ => value)}
        placeholder={j|Hasło|j}
        htmlType="password"
      />
      <div
        className={
          [
            Height(H24),
            Display(Flex),
            AlignItems(ItemsCenter),
            JustifyContent(JustifyCenter),
          ]
          ->make
        }>
        {switch (error) {
         | Some(error) =>
           Js.log(error);
           <Text color=`red> "Niepoprawne dane logowania" </Text>;
         | None => React.null
         }}
      </div>
      <Button loading=fetching onClick={_ => signIn()}>
        <Text color=`white>
          {fetching ? {j|Logowanie|j} : {j|Zaloguj się|j}}
        </Text>
      </Button>
    </div>
  </div>;
};